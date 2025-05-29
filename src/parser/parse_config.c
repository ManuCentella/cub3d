/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:37:15 by mcentell          #+#    #+#             */
/*   Updated: 2025/05/28 18:45:24 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_start(char **lines, int start_index)
{
	int	i;
	int	j;

	i = start_index;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ' || lines[i][j] == '\n' || lines[i][j] == '\r'
			|| lines[i][j] == '\t')
			j++;
		if (lines[i][j] == '\0')
			i++;
		else
			break ;
	}
	if (!lines[i])
		return (-1);
	if (lines[i][0] == '1' || lines[i][0] == '0' || lines[i][0] == ' '
		|| lines[i][0] == 'N' || lines[i][0] == 'S' || lines[i][0] == 'E'
		|| lines[i][0] == 'W')
		return (i);
	return (-1);
}

static int	try_find_map(char **lines, int i, int *map_start)
{
	int	idx;

	idx = find_map_start(lines, i);
	if (idx != -1)
	{
		*map_start = idx;
		return (1);
	}
	return (0);
}

static int	handle_map_line(char *line, char **lines, int idx, int *map_start)
{
	char	*t;
	int		ret;

	t = ft_strtrim(line, " \t\r\n");
	if (!t)
		return (-1);
	if (t[0] == '\0')
	{
		free(t);
		return (0);
	}
	free(t);
	ret = try_find_map(lines, idx, map_start);
	if (ret)
		return (1);
	return (-1);
}

static int	process_map_start(char *line, char **lines, int idx, int *map_start)
{
	int	rc;

	rc = handle_map_line(line, lines, idx, map_start);
	if (rc == 1)
		return (1);
	if (rc == -1)
	{
		printf("Error\nInvalid or duplicated config line\n");
		return (-1);
	}
	return (0);
}

int	parse_config(char **lines, t_config *cfg, int *map_start)
{
	int	i;
	int	status;
	int	rc;

	i = 0;
	*map_start = -1;
	while (lines[i])
	{
		status = dispatch_parse_line(lines[i], cfg);
		if (status == -1)
			return (0);
		if (status == 0)
		{
			rc = process_map_start(lines[i], lines, i, map_start);
			if (rc == 1)
				return (1);
			if (rc == -1)
				return (0);
		}
		i++;
	}
	printf("Error\nMap not found in the file\n");
	return (0);
}

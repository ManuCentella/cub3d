/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:02:32 by mcentell          #+#    #+#             */
/*   Updated: 2025/06/02 19:28:31 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_lines(char **lines)
{
	int	i = 0;

	while (lines[i])
		i++;
	return (i);
}

static int	get_max_width(char **lines, int height)
{
	int	i, len, max = 0;

	for (i = 0; i < height; i++)
	{
		len = 0;
		while (lines[i][len] && lines[i][len] != '\n' && lines[i][len] != '\r')
			len++;
		if (len > max)
			max = len;
	}
	return (max);
}

static void	free_partial_map(char **map, int last_index)
{
	while (last_index >= 0)
		free(map[last_index--]);
	free(map);
}

static char	*process_map_line(char *line, int max_width)
{
	char	*new_line;
	int		len = 0;
	int		i;

	while (line[len] && line[len] != '\n' && line[len] != '\r')
		len++;
	new_line = malloc(sizeof(char) * (max_width + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < len && i < max_width)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < max_width)
	{
		new_line[i] = ' ';  // ✅ No usamos '1', dejamos hueco para que la validación detecte errores reales
		i++;
	}
	new_line[max_width] = '\0';
	return (new_line);
}

int	parse_map(char **lines, t_config *cfg)
{
	int		h = count_map_lines(lines);
	int		w = get_max_width(lines, h);
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (h + 1));
	if (!map)
		return (0);
	i = 0;
	while (i < h)
	{
		map[i] = process_map_line(lines[i], w);
		if (!map[i])
		{
			free_partial_map(map, i - 1);
			return (0);
		}
		i++;
	}
	map[h] = NULL;
	cfg->map = map;
	cfg->map_height = h;
	cfg->map_width = w;
	return (1);
}

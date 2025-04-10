/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dispathc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:09:50 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/10 17:10:35 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_texture_line(char *trimmed)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 || ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0 || ft_strncmp(trimmed, "EA ",
			3) == 0)
		return (1);
	return (0);
}

static int	is_color_line(char *trimmed)
{
	if (ft_strncmp(trimmed, "F ", 2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0)
		return (1);
	return (0);
}

int	dispatch_parse_line(char *line, t_config *cfg)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_strtrim(line, " \t\r\n");
	if (!trimmed)
		return (-1);
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		return (0);
	}
	if (is_texture_line(trimmed))
		ret = parse_texture_line(trimmed, cfg);
	else if (is_color_line(trimmed))
		ret = parse_color_line(trimmed, cfg);
	else
		ret = 0;
	free(trimmed);
	if (ret > 0)
		return (1);
	else if (ret == 0)
		return (0);
	else
		return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:52:54 by mcentell          #+#    #+#             */
/*   Updated: 2025/05/28 17:40:58 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	report_map_error(const char *msg, int *has_error)
{
	if (*has_error == 0)
		printf("Error\n");
	printf("%s\n", msg);
	*has_error = 1;
	return (1);
}

int	is_map_line(const char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0')
			return (1);
		line++;
	}
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D' || c == ' ');
}

char	get_map_cell(t_config *cfg, int y, int x)
{
	if (y < 0 || y >= cfg->map_height || x < 0 || x >= cfg->map_width)
		return (' ');
	return (cfg->map[y][x]);
}

int is_cell_closed(t_config *cfg, int y, int x)
{
	char	c = get_map_cell(cfg, y, x);

	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	if (y - 1 < 0 || get_map_cell(cfg, y - 1, x) == ' ')
		return (0);
	if (y + 1 >= cfg->map_height || get_map_cell(cfg, y + 1, x) == ' ')
		return (0);
	if (x - 1 < 0 || get_map_cell(cfg, y, x - 1) == ' ')
		return (0);
	if (x + 1 >= (int)ft_strlen(cfg->map[y]) || get_map_cell(cfg, y, x + 1) == ' ')
		return (0);

	return (1);
}




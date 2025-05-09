/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:52:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/28 10:35:07 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	report_missing(const char *desc, int condition, int *has_error)
{
	if (condition)
	{
		if (*has_error == 0)
			printf("Error\n");
		printf("%s\n", desc);
		*has_error = 1;
		return (1);
	}
	return (0);
}

int	validate_config(t_config *cfg)
{
	int	has_error;

	has_error = 0;
	report_missing("Missing NO texture", !cfg->no_path, &has_error);
	report_missing("Missing SO texture", !cfg->so_path, &has_error);
	report_missing("Missing WE texture", !cfg->we_path, &has_error);
	report_missing("Missing EA texture", !cfg->ea_path, &has_error);
	report_missing("Missing floor color (F)", cfg->floor_color == -1,
		&has_error);
	report_missing("Missing ceiling color (C)", cfg->ceiling_color == -1,
		&has_error);
	return (!has_error);
}

static int	validate_map_row(t_config *cfg, int row, int *player_count,
		int *has_error)
{
	int		x;
	int		error;
	char	c;

	error = 0;
	x = 0;
	while (x < cfg->map_width)
	{
		c = cfg->map[row][x];
		if (!is_valid_map_char(c))
		{
			report_map_error("Invalid character in map", has_error);
			error = 1;
		}
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			(*player_count)++;
		if (!is_cell_closed(cfg, row, x))
		{
			report_map_error("Map not closed by walls", has_error);
			error = 1;
		}
		x++;
	}
	return (error);
}
static int	is_door_invalid(t_config *cfg, int y, int x)
{
	// Comprobar si está en el borde
	if (y == 0 || y == cfg->map_height - 1 || x == 0 || x == cfg->map_width - 1)
		return (1);
	// Comprobar si está tocando un espacio
	if (get_map_cell(cfg, y - 1, x) == ' ' || get_map_cell(cfg, y + 1, x) == ' ' ||
		get_map_cell(cfg, y, x - 1) == ' ' || get_map_cell(cfg, y, x + 1) == ' ')
		return (1);
	return (0);
}
static int	validate_doors_properly(t_config *cfg, int *has_error)
{
	int	x, y;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			if (cfg->map[y][x] == 'D' && is_door_invalid(cfg, y, x))
			{
				report_map_error("Invalid door placement", has_error);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map(t_config *cfg)
{
	int	y;
	int	total_error;
	int	total_player;

	total_error = 0;
	total_player = 0;
	y = 0;
	while (y < cfg->map_height)
	{
		validate_map_row(cfg, y, &total_player, &total_error);
		y++;
	}
	if (validate_doors_properly(cfg, &total_error))
		return (0);
	if (total_player != 1)
		report_map_error("Map must have exactly one player position",
			&total_error);
	return (!total_error);
}

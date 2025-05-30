/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:52:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/05/29 14:07:46 by mcentell         ###   ########.fr       */
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

static void	check_wall_at_cell(t_config *cfg, int row, int x, int *has_error)
{
	if (!is_cell_closed(cfg, row, x) && !cfg->reported_open_wall)
	{
		report_map_error("Map not closed by walls", has_error);
		cfg->reported_open_wall = 1;
		cfg->map_row_error = 1;
	}
}

static int	validate_map_row(t_config *cfg, int row, int *player_count,
		int *has_error)
{
	int		x;
	char	c;

	cfg->reported_invalid_char = 0;
	cfg->reported_open_wall = 0;
	cfg->map_row_error = 0;
	x = 0;
	while (x < cfg->map_width)
	{
		c = cfg->map[row][x];
		if (!is_valid_map_char(c) && !cfg->reported_invalid_char)
		{
			report_map_error("Invalid character in map", has_error);
			cfg->reported_invalid_char = 1;
			cfg->map_row_error = 1;
		}
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			(*player_count)++;
		check_wall_at_cell(cfg, row, x, has_error);
		x++;
	}
	return (cfg->map_row_error);
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
	if (total_player != 1)
		report_map_error("Map must have exactly one player position",
			&total_error);
	return (!total_error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:52:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/09 18:10:41 by mcentell         ###   ########.fr       */
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

int	validate_map(t_config *cfg)
{
	int	y;
	int	x;
	int	player_count;
	int	has_error;

	has_error = 0;
	player_count = 0;
	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			validate_cell(cfg, y, x, &player_count, &has_error);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		report_map_error("Map must have exactly one player position",
			&has_error);
	return (!has_error);
}

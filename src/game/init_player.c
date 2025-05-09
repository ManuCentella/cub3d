/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:29:41 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/23 12:15:46 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// -----------------------------------------------------------------------------
// src/game/init_player.c
// -----------------------------------------------------------------------------

static char	find_player_spawn(t_config *cfg, int *out_x, int *out_y)
{
	int		y;
	int		x;
	char	**map;
	char	c;

	map = cfg->map;
	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			c = map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				*out_x = x;
				*out_y = y;
				return (c);
			}
			x++;
		}
		y++;
	}
	return ('\0');
}

static void	init_direction(t_player *player, char c, int px, int py)
{
	player->x = px + 0.5;
	player->y = py + 0.5;
	if (c == 'N')
		player->dir_x = 0, player->dir_y = -1;
	else if (c == 'S')
		player->dir_x = 0, player->dir_y = 1;
	else if (c == 'E')
		player->dir_x = 1, player->dir_y = 0;
	else // 'W'
		player->dir_x = -1, player->dir_y = 0;
	player->plane_x = -0.66 * player->dir_y;
	player->plane_y = 0.66 * player->dir_x;
}

void	init_player(t_game *game)
{
	int		px;
	int		py;
	char	spawn;

	spawn = find_player_spawn(game->config, &px, &py);
	if (spawn == '\0')
		return ; // o manejar error de “sin spawn” si lo prefieres
	init_direction(&game->player, spawn, px, py);
}

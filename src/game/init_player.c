/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:29:41 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/14 12:29:54 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	char	**map = game->config->map;
	int		y = 0;
	int		x;

	while (y < game->config->map_height)
	{
		x = 0;
		while (x < game->config->map_width)
		{
			char c = map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				if (c == 'N')
					game->player.dir_x = 0, game->player.dir_y = -1;
				if (c == 'S')
					game->player.dir_x = 0, game->player.dir_y = 1;
				if (c == 'E')
					game->player.dir_x = 1, game->player.dir_y = 0;
				if (c == 'W')
					game->player.dir_x = -1, game->player.dir_y = 0;
				// Plano perpendicular
				game->player.plane_x = -0.66 * game->player.dir_y;
				game->player.plane_y = 0.66 * game->player.dir_x;
				return ;
			}
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:13:10 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/15 17:27:25 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_cell(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale;
	int	px;
	int	py;

	scale = 15;
	px = x * scale;
	py = y * scale;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			put_pixel(&game->image, px + j, py + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_grid(t_game *game)
{
	int	x;
	int	y;
	char	**map;

	map = game->config->map;
	y = 0;
	while (y < game->config->map_height)
	{
		x = 0;
		while (x < game->config->map_width)
		{
			if (map[y][x] == '1')
				draw_cell(game, x, y, 0x555555);
			else
				draw_cell(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

static void	draw_line(t_image *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
static void	draw_player_and_rays(t_game *game)
{
	int	scale;
	int	player_x;
	int	player_y;
	int	len;

	scale = 5;
	player_x = (int)(game->player.x * scale);
	player_y = (int)(game->player.y * scale);
	put_pixel(&game->image, player_x, player_y, 0xFF0000);
	len = 10;
	draw_line(&game->image, player_x, player_y,
		player_x + (int)(game->player.dir_x * len),
		player_y + (int)(game->player.dir_y * len),
		0x00FF00);
	draw_line(&game->image, player_x, player_y,
		player_x + (int)((game->player.dir_x + game->player.plane_x) * len),
		player_y + (int)((game->player.dir_y + game->player.plane_y) * len),
		0x66CCFF);
	draw_line(&game->image, player_x, player_y,
		player_x + (int)((game->player.dir_x - game->player.plane_x) * len),
		player_y + (int)((game->player.dir_y - game->player.plane_y) * len),
		0x66CCFF);
}

void	draw_minimap(t_game *game)
{
	draw_minimap_grid(game);
	draw_player_and_rays(game);
}

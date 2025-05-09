/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:13:10 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/21 20:17:19 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int	is_end(int pts[4])
{
	if (pts[0] == pts[2] && pts[1] == pts[3])
		return (1);
	return (0);
}

static void	update_step(int pts[4], int *err, int p[4])
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 >= p[1])
	{
		*err += p[1];
		pts[0] += p[2];
	}
	if (e2 <= p[0])
	{
		*err += p[0];
		pts[1] += p[3];
	}
}

static void	draw_line(int pts[4], t_image *img, int color)
{
	int	p[4];
	int	err;

	p[0] = abs(pts[2] - pts[0]);
	p[1] = -abs(pts[3] - pts[1]);
	if (pts[0] < pts[2])
		p[2] = 1;
	else
		p[2] = -1;
	if (pts[1] < pts[3])
		p[3] = 1;
	else
		p[3] = -1;
	err = p[0] + p[1];
	while (is_end(pts) == 0)
	{
		put_pixel(img, pts[0], pts[1], color);
		update_step(pts, &err, p);
	}
	put_pixel(img, pts[0], pts[1], color);
}

static void	draw_cell(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale;
	int	px;
	int	py;

	scale = MINIMAP_SCALE;
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
	int		x;
	int		y;
	char	**map;
	int		color;

	map = game->config->map;
	y = 0;
	while (y < game->config->map_height)
	{
		x = 0;
		while (x < game->config->map_width)
		{
			if (map[y][x] == '1')
				color = 0x555555;
			else
				color = 0x000000;
			draw_cell(game, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_player_marker(t_game *game, int px, int py)
{
	int	offset;

	offset = -2;
	while (offset <= 2)
	{
		put_pixel(&game->image, px + offset, py, 0xFF0000);
		put_pixel(&game->image, px, py + offset, 0xFF0000);
		offset++;
	}
}

/* Función auxiliar para calcular el color de la línea */
static int	calc_ray_color(double f)
{
	int	intensity;

	intensity = (int)(255 * (1 - fabs(f)));
	if (intensity < 0)
		intensity = 0;
	return (intensity << 8);
}

static void	get_ray_endpoint(t_game *game, double f, double *map_x, double *map_y)
{
	double	dir_x;
	double	dir_y;
	int		step;
	int		cell_x;
	int		cell_y;

	dir_x = game->player.dir_x + game->player.plane_x * f;
	dir_y = game->player.dir_y + game->player.plane_y * f;
	*map_x = game->player.x;
	*map_y = game->player.y;
	step = 0;
	while (step < 30)
	{
		cell_x = (int)(*map_x);
		cell_y = (int)(*map_y);
		if (cell_y < 0 || cell_y >= game->config->map_height
			|| cell_x < 0 || cell_x >= game->config->map_width
			|| game->config->map[cell_y][cell_x] == '1')
			break ;
		*map_x += dir_x * 0.05;
		*map_y += dir_y * 0.05;
		step++;
	}
}

static void	draw_vision_ray(t_game *game, int px, int py, double f)
{
	double	map_x;
	double	map_y;
	int		pts[4];
	int		color;
	int		scale;

	scale = MINIMAP_SCALE;
	get_ray_endpoint(game, f, &map_x, &map_y);
	pts[0] = px;
	pts[1] = py;
	pts[2] = (int)(map_x * scale);
	pts[3] = (int)(map_y * scale);
	color = calc_ray_color(f);
	draw_line(pts, &game->image, color);
}


static void	draw_player_vision(t_game *game, int px, int py)
{
	double	f;
	double	step;

	step = 0.05;
	f = -1.0;
	while (f <= 1.0)
	{
		draw_vision_ray(game, px, py, f);
		f += step;
	}
}

static void	draw_player_and_rays(t_game *game)
{
	int	scale;
	int	player_x;
	int	player_y;

	scale = MINIMAP_SCALE;
	player_x = (int)(game->player.x * scale);
	player_y = (int)(game->player.y * scale);
	draw_player_marker(game, player_x, player_y);
	draw_player_vision(game, player_x, player_y);
}

void	draw_minimap(t_game *game)
{
	draw_minimap_grid(game);
	draw_player_and_rays(game);
}

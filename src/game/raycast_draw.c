/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:12:21 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/15 16:32:52 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	compute_projection(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;

	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;

	// Punto exacto del impacto en el eje de la pared
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);

	// Coordenada X dentro de la textura
	ray->tex_x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = TEXTURE_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = TEXTURE_WIDTH - ray->tex_x - 1;
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	// Pintar cielo
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->image, x, y, game->config->ceiling_color);
		y++;
	}

	// Cálculo para textura
	step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;

	// Pintar pared con textura
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		color = game->textures[ray->tex_num].data[TEXTURE_WIDTH * tex_y + ray->tex_x];
		put_pixel(&game->image, x, y, color);
		y++;
	}

	// Pintar suelo
	while (y < SCREEN_HEIGHT)
	{
		put_pixel(&game->image, x, y, game->config->floor_color);
		y++;
	}
}

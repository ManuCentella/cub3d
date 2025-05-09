/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:12:21 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/23 12:41:13 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

static void compute_line_bounds(t_ray *ray)
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
}

static void compute_wall_hit(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
        ray->wall_x = game->player.y
            + ray->perp_wall_dist * ray->ray_dir_y;
    else
        ray->wall_x = game->player.x
            + ray->perp_wall_dist * ray->ray_dir_x;
    ray->wall_x -= floor(ray->wall_x);
}

static void compute_tex_x(t_ray *ray)
{
    int tx;

    tx = (int)(ray->wall_x * TEXTURE_WIDTH);
    if (ray->side == 0 && ray->ray_dir_x > 0)
        tx = TEXTURE_WIDTH - tx - 1;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        tx = TEXTURE_WIDTH - tx - 1;
    ray->tex_x = tx;
}

void compute_projection(t_game *game, t_ray *ray)
{
    compute_line_bounds(ray);
    compute_wall_hit(game, ray);
    compute_tex_x(ray);
}
// Implementación en raycast_draw.c
static void draw_ceiling(t_game *game, int x, int y_end)
{
    int y = 0;
    while (y < y_end)
        put_pixel(&game->image, x, y++, game->config->ceiling_color);
}

static void draw_floor(t_game *game, int x, int y_start)
{
    int y = y_start;
    while (y < SCREEN_HEIGHT)
        put_pixel(&game->image, x, y++, game->config->floor_color);
}

static void draw_wall_slice(t_game *game, t_ray *ray, int x)
{
    int y = ray->draw_start;
    double step = (double)TEXTURE_HEIGHT / ray->line_height;
    double tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
    while (y <= ray->draw_end)
    {
        int tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
        tex_pos += step;
        int color = game->textures[ray->tex_num].data[TEXTURE_WIDTH * tex_y + ray->tex_x];
        put_pixel(&game->image, x, y++, color);
    }
}

void draw_column(t_game *game, t_ray *ray, int x)
{
    draw_ceiling(game, x, ray->draw_start);
    draw_wall_slice(game, ray, x);
    draw_floor(game, x, ray->draw_end + 1);
}

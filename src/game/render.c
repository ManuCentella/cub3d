/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:00:07 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/22 19:24:48 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/*
 * Crea una imagen en memoria y obtiene acceso a su buffer.
 */
void	init_image(t_game *game)
{
	game->image.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->image.addr = mlx_get_data_addr(game->image.img, &game->image.bpp,
			&game->image.line_length, &game->image.endian);
}

/*
 * Colorea un píxel individual en la imagen si está dentro de pantalla.
 */
void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
 * Ciclo principal: lanza un rayo por cada columna de pantalla y la dibuja.
 */
void render_frame(t_game *game)
{
    // Avanza la animación de la puerta antes de dibujar
    update_door(game);

    // Raycasting columna a columna
    int x;
    t_ray ray;

    for (x = 0; x < SCREEN_WIDTH; x++)
    {
        calculate_ray_values(game, &ray, x);
        perform_dda(game, &ray);
        compute_projection(game, &ray);
        draw_column(game, &ray, x);
    }

    // Minimapa y presentación en pantalla
    draw_minimap(game);
    mlx_put_image_to_window(game->mlx, game->win,
        game->image.img, 0, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:01:41 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/15 17:19:14 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* a"b c"d
 * Mueve al jugador hacia adelante si no hay pared.
 */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (game->config->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->config->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
}

/*
 * Mueve al jugador hacia atrás si no hay pared.
 */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (game->config->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->config->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
}

/*
 * Mueve al jugador hacia la izquierda (strafe).
 */
void	move_left(t_game *game)
{
	double	perp_x;
	double	perp_y;
	double	new_x;
	double	new_y;

	perp_x = game->player.dir_y;
	perp_y = -game->player.dir_x;
	new_x = game->player.x + perp_x * MOVE_SPEED;
	new_y = game->player.y + perp_y * MOVE_SPEED;
	if (game->config->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->config->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
}

/*
 * Mueve al jugador hacia la derecha (strafe).
 */
void	move_right(t_game *game)
{
	double	perp_x;
	double	perp_y;
	double	new_x;
	double	new_y;

	perp_x = -game->player.dir_y;
	perp_y = game->player.dir_x;
	new_x = game->player.x + perp_x * MOVE_SPEED;
	new_y = game->player.y + perp_y * MOVE_SPEED;
	if (game->config->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->config->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
}

/*
 * Gira el jugador a la izquierda (rotación antihoraria).
 */
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	angle;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	angle = -ROT_SPEED;
	game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
		* cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y
		* cos(angle);
}

/*
 * Gira el jugador a la derecha (rotación horaria).
 */
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	angle;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	angle = ROT_SPEED;
	game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
		* cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y
		* cos(angle);
}

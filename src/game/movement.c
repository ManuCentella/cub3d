/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:01:41 by mcentell          #+#    #+#             */
/*   Updated: 2025/05/19 16:00:52 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_free_cell(t_game *game, int y, int x)
{
	char	c;

	c = get_map_cell(game->config, y, x);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	move_forward(t_game *game)
{
	double	nx;
	double	ny;
	double	offset;
	int		cell_x;

	nx = game->player.x + game->player.dir_x * MOVE_SPEED;
	ny = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (game->player.dir_x > 0)
		offset = COLLIDE_RADIUS;
	else
		offset = -COLLIDE_RADIUS;
	cell_x = (int)(nx + offset);
	if (is_free_cell(game, (int)game->player.y, cell_x))
		game->player.x = nx;
	if (game->player.dir_y > 0)
		offset = COLLIDE_RADIUS;
	else
		offset = -COLLIDE_RADIUS;
	cell_x = (int)(game->player.x);
	if (is_free_cell(game, (int)(ny + offset), cell_x))
		game->player.y = ny;
}

void	move_left(t_game *game)
{
	double	nx;
	double	ny;
	double	offset;
	int		cell_x;

	nx = game->player.x + game->player.dir_y * MOVE_SPEED;
	ny = game->player.y - game->player.dir_x * MOVE_SPEED;
	if (game->player.dir_y > 0)
		offset = COLLIDE_RADIUS;
	else
		offset = -COLLIDE_RADIUS;
	cell_x = (int)(nx + offset);
	if (is_free_cell(game, (int)game->player.y, cell_x))
		game->player.x = nx;
	if (-game->player.dir_x > 0)
		offset = COLLIDE_RADIUS;
	else
		offset = -COLLIDE_RADIUS;
	cell_x = (int)(game->player.x);
	if (is_free_cell(game, (int)(ny + offset), cell_x))
		game->player.y = ny;
}

void	move_right(t_game *game)
{
	double	nx;
	double	ny;
	double	offset;
	int		cell_x;

	nx = game->player.x - game->player.dir_y * MOVE_SPEED;
	ny = game->player.y + game->player.dir_x * MOVE_SPEED;
	if (-game->player.dir_y > 0)
		offset = COLLIDE_RADIUS;
	else
		offset = -COLLIDE_RADIUS;
	cell_x = (int)(nx + offset);
	if (is_free_cell(game, (int)game->player.y, cell_x))
		game->player.x = nx;
	if (game->player.dir_x > 0)
		offset = COLLIDE_RADIUS;
	else
		offset = -COLLIDE_RADIUS;
	cell_x = (int)(game->player.x);
	if (is_free_cell(game, (int)(ny + offset), cell_x))
		game->player.y = ny;
}

void	move_backward(t_game *game)
{
	double	nx;
	double	ny;
	double	offset;
	int		cell_x;

	nx = game->player.x - game->player.dir_x * MOVE_SPEED;
	ny = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (game->player.dir_x < 0)
		offset = COLLIDE_RADIUS;
	else
		offset = -COLLIDE_RADIUS;
	cell_x = (int)(nx + offset);
	if (is_free_cell(game, (int)game->player.y, cell_x))
		game->player.x = nx;
	if (game->player.dir_y < 0)
		offset = COLLIDE_RADIUS;
	else
		offset = -COLLIDE_RADIUS;
	cell_x = (int)(game->player.x);
	if (is_free_cell(game, (int)(ny + offset), cell_x))
		game->player.y = ny;
}

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

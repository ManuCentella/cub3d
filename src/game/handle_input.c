/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:20:48 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/14 17:27:32 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Captura las teclas pulsadas y llama a la función correspondiente.
 */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC
		close_window(game);
	else if (keycode == 119) // W
		move_forward(game);
	else if (keycode == 115) // S
		move_backward(game);
	else if (keycode == 97) // A
		move_left(game);
	else if (keycode == 100) // D
		move_right(game);
	else if (keycode == 65361) // ←
		rotate_left(game);
	else if (keycode == 65363) // →
		rotate_right(game);
	render_frame(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	else if (keycode == 119)
		game->keys.w = 1;
	else if (keycode == 115)
		game->keys.s = 1;
	else if (keycode == 97)
		game->keys.a = 1;
	else if (keycode == 100)
		game->keys.d = 1;
	else if (keycode == 65361)
		game->keys.left = 1;
	else if (keycode == 65363)
		game->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->keys.w = 0;
	else if (keycode == 115)
		game->keys.s = 0;
	else if (keycode == 97)
		game->keys.a = 0;
	else if (keycode == 100)
		game->keys.d = 0;
	else if (keycode == 65361)
		game->keys.left = 0;
	else if (keycode == 65363)
		game->keys.right = 0;
	return (0);
}

int	handle_continuous_input(t_game *game)
{
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
	render_frame(game);
	return (0);
}

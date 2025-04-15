/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:06:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/15 17:24:29 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->config->map);
	free_config(game->config);
	free(game);
	exit(0);
	return (0);
}

t_game	*init_game_window(t_config *cfg)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), NULL);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
	{
		free(game->mlx);
		return (free(game), NULL);
	}
	game->config = cfg;

	// Inicializa las teclas en 0
	ft_memset(&game->keys, 0, sizeof(t_keys));

	// Hooks para eventos
	mlx_hook(game->win, 17, 0, close_window, game);          // Cierre ventana 
	mlx_hook(game->win, 2, 1L << 0, key_press, game);        // Pulsar tecla
	mlx_hook(game->win, 3, 1L << 1, key_release, game);      // Soltar tecla
	mlx_loop_hook(game->mlx, handle_continuous_input, game); // Movimiento continuo

	return (game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:54:12 by mcentell          #+#    #+#             */
/*   Updated: 2025/06/02 19:48:27 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cleanup_game(t_game *game)
{
	int i;

	if (!game)
		return;

	for (i = 0; i < TOTAL_TEXTURES; i++)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
	}

	if (game->image.img)
		mlx_destroy_image(game->mlx, game->image.img);

	if (game->win)
		mlx_destroy_window(game->mlx, game->win);

	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}

	if (game->config)
	{
		if (game->config->map)
			free_map(game->config->map);
		free_config(game->config);
	}

	free(game);
}


int	main(int argc, char **argv)
{
	t_config	cfg;
	t_game		*game;

	if (argc != 2)
		return (printf("Uso: ./cub3d <archive.cub>\n"), 1);
	if (!run_parser(&cfg, argv[1]))
		return (1);
	game = init_game_window(&cfg);
	if (!game)
		return (free_map(cfg.map), free_config(&cfg), 1);

	if (!load_textures(game))
	{
		cleanup_game(game);
		return (1);
	}
	init_player(game);
	init_image(game);
	render_frame(game);
	mlx_loop(game->mlx);
	cleanup_game(game);
	return (0);
}

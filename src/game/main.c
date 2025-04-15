/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:54:12 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/15 17:00:35 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_config	cfg;
	t_game		*game;

	if (argc != 2)
		return (printf("Uso: ./cub3d <archivo.cub>\n"), 1);
	if (!run_parser(&cfg, argv[1]))
		return (1);
	game = init_game_window(&cfg);
	if (!game)
		return (free_map(cfg.map), free_config(&cfg), 1);

	if (!load_textures(game))
	{
		printf("Error cargando texturas\n");
		return (free(game), free_map(cfg.map), free_config(&cfg), 1);
	}
	init_player(game);
	init_image(game);
	render_frame(game);
	mlx_loop(game->mlx);
	free(game);
	free_map(cfg.map);
	free_config(&cfg);
	return (0);
}

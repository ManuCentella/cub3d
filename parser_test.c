/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:10:22 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/09 18:16:35 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_config	cfg;
	char		**lines;
	int			map_start;

	if (argc != 2)
	{
		printf("Uso: ./cub3d <archivo.cub>\n");
		return (1);
	}

	ft_memset(&cfg, 0, sizeof(t_config));
	cfg.floor_color = -1;
	cfg.ceiling_color = -1;

	lines = read_cub_file(argv[1]);
	if (!lines)
	{
		printf("Error\nNo se pudo leer el archivo .cub\n");
		return (1);
	}

	if (!parse_config(lines, &cfg, &map_start))
	{
		printf("Error\nFalló el parseo de la configuración\n");
		return (1);
	}

	if (!validate_config(&cfg))
		return (1);

	if (!parse_map(&lines[map_start], &cfg))
	{
		printf("Error\nFalló el parseo del mapa\n");
		return (1);
	}

	if (!validate_map(&cfg))
		return (1);

	printf("✅ Todo OK: configuración y mapa válidos.\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:50:27 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/14 11:50:59 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	run_parser(t_config *cfg, const char *filename)
{
	char	**lines;
	int		map_start;

	ft_memset(cfg, 0, sizeof(t_config));
	cfg->floor_color = -1;
	cfg->ceiling_color = -1;

	lines = read_cub_file(filename);
	if (!lines)
		return (printf("Error\nNo se pudo leer el archivo .cub\n"), 0);
	if (!parse_config(lines, cfg, &map_start))
		return (free_split(lines), 0);
	if (!validate_config(cfg))
		return (free_split(lines), 0);
	if (!parse_map(&lines[map_start], cfg))
		return (printf("Error\nFalló el parseo del mapa\n"), free_split(lines), 0);
	if (!validate_map(cfg))
		return (free_split(lines), 0);

	free_split(lines);
	return (1);
}

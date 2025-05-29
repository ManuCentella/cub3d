/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:50:27 by mcentell          #+#    #+#             */
/*   Updated: 2025/05/28 19:44:48 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_all_on_error(t_config *cfg, char **lines)
{
	free_split(lines);
	free_config(cfg);
	free_map(cfg->map);
}

static int	load_and_validate_config(t_config *cfg, char ***lines_ptr,
		const char *filename, int *map_start)
{
	char	**lines;

	lines = read_cub_file(filename);
	if (!lines)
	{
		printf("Error\nCould not read .cub file\n");
		return (0);
	}
	if (!parse_config(lines, cfg, map_start) || cfg->error_already_reported
		|| !validate_config(cfg))
	{
		free_all_on_error(cfg, lines);
		return (0);
	}
	*lines_ptr = lines;
	return (1);
}

/*
 * 2) Parsea y valida el mapa; en caso de fallo libera y retorna 0.
 */
static int	parse_and_validate_map(t_config *cfg, char **lines, int map_start)
{
	if (!parse_map(&lines[map_start], cfg))
	{
		printf("Error\nMap parsing failed\n");
		free_all_on_error(cfg, lines);
		return (0);
	}
	if (!validate_map(cfg))
	{
		free_all_on_error(cfg, lines);
		return (0);
	}
	return (1);
}

int	run_parser(t_config *cfg, const char *filename)
{
	char	**lines;
	int		map_start;

	ft_memset(cfg, 0, sizeof(*cfg));
	cfg->floor_color = -1;
	cfg->ceiling_color = -1;
	cfg->map = NULL;
	cfg->error_already_reported = 0;
	if (!load_and_validate_config(cfg, &lines, filename, &map_start))
		return (0);
	if (!parse_and_validate_map(cfg, lines, map_start))
		return (0);
	free_split(lines);
	return (1);
}

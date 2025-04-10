/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:37:15 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/10 17:10:27 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_start(char **lines, int start_index)
{
	int	i;
	int	j;

	i = start_index;
	while (lines[i])
	{
		j = 0;
		// Ignorar espacios, tabs, saltos de línea y retorno de carro
		while (lines[i][j] == ' ' || lines[i][j] == '\n' || lines[i][j] == '\r'
			|| lines[i][j] == '\t')
			j++;
		// Si la línea solo tiene esos caracteres, la consideramos vacía
		if (lines[i][j] == '\0')
			i++;
		else
			break ;
	}
	if (!lines[i])
		return (-1);
	// Verifica si la línea empieza con un carácter típico del mapa
	if (lines[i][0] == '1' || lines[i][0] == '0' || lines[i][0] == ' '
		|| lines[i][0] == 'N' || lines[i][0] == 'S' || lines[i][0] == 'E'
		|| lines[i][0] == 'W')
		return (i);
	return (-1);
}

static int	try_find_map(char **lines, int i, int *map_start)
{
	int	index;

	index = find_map_start(lines, i);
	if (index != -1)
	{
		*map_start = index;
		return (1);
	}
	return (0);
}

int	parse_config(char **lines, t_config *cfg, int *map_start)
{
	int	i;
	int	status;
	int	has_error;
	int	found_map;

	i = 0;
	has_error = 0;
	found_map = 0;
	while (lines[i])
	{
		status = dispatch_parse_line(lines[i], cfg);
		if (status == -1)
			has_error = 1;
		else if (!found_map && status == 0)
			found_map = try_find_map(lines, i, map_start);
		i++;
	}
	if (!found_map)
	{
		printf("Error\nMapa no encontrado en el archivo\n");
		return (0);
	}
	return (!has_error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:37:15 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/09 14:26:48 by mcentell         ###   ########.fr       */
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
		while (lines[i][j] == ' ' || lines[i][j] == '\n' ||
		       lines[i][j] == '\r' || lines[i][j] == '\t')
			j++;
		// Si la línea solo tiene esos caracteres, la consideramos vacía
		if (lines[i][j] == '\0')
			i++;
		else
			break;
	}
	if (!lines[i])
		return (-1);
	// Verifica si la línea empieza con un carácter típico del mapa
	if (lines[i][0] == '1' || lines[i][0] == '0' || lines[i][0] == ' ' ||
		lines[i][0] == 'N' || lines[i][0] == 'S' || lines[i][0] == 'E' || lines[i][0] == 'W')
		return (i);
	return (-1);
}



int	parse_config(char **lines, t_config *cfg, int *map_start)
{
	int	i;
	int	status;

	i = 0;
	while (lines[i])
	{
		status = dispatch_parse_line(lines[i], cfg);
		if (status == -1)
			return (0);
		if (status == 0)
		{
			int index = find_map_start(lines, i);
			if (index == -1)
				return (0);
			*map_start = index;
			return (1);
		}
		i++;
	}
	return (0); // mapa no encontrado
}

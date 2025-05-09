/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:52:54 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/22 15:59:00 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	report_map_error(const char *msg, int *has_error)
{
	if (*has_error == 0)
		printf("Error\n");
	printf("%s\n", msg);
	*has_error = 1;
	return (1);
}

// Verifica si un carácter está dentro del set permitido
int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D' || c == ' ');
}

// Verifica si el carácter está dentro del mapa y no fuera de límites
char	get_map_cell(t_config *cfg, int y, int x)
{
	if (y < 0 || y >= cfg->map_height || x < 0 || x >= cfg->map_width)
		return (' '); // Fuera de mapa → considerado espacio
	return (cfg->map[y][x]);
}

// Verifica que un carácter no esté al borde o tocando un espacio
int	is_cell_closed(t_config *cfg, int y, int x)
{
	char	c;

	c = get_map_cell(cfg, y, x);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		// Revisamos las 4 direcciones
		if (get_map_cell(cfg, y - 1, x) == ' ')
			return (0);
		if (get_map_cell(cfg, y + 1, x) == ' ')
			return (0);
		if (get_map_cell(cfg, y, x - 1) == ' ')
			return (0);
		if (get_map_cell(cfg, y, x + 1) == ' ')
			return (0);
	}
	return (1);
}

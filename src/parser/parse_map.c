/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:02:32 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/10 17:43:04 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Devuelve el número de líneas del array 'lines' hasta el NULL.
 */
static int	count_map_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

/*
 * Recorre las líneas y devuelve el ancho máximo entre ellas.
 */
static int	get_max_width(char **lines, int height)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (i < height)
	{
		len = ft_strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

/*
 * Recibe un array de líneas (que corresponden al mapa tal como se lee),
 * duplica cada línea y las rellena con espacios hasta que todas tengan la
 * misma longitud (para un mapa rectangular). Luego, guarda el resultado en cfg.
 * Devuelve 1 si se procesa correctamente, o 0 en caso de error.
 */

static void	copy_and_pad(char *dest, const char *src, int max_width)
{
	int	i;

	i = 0;
	while (src[i] && i < max_width)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < max_width)
	{
		dest[i] = ' ';
		i++;
	}
	dest[max_width] = '\0';
}

static char	*process_map_line(char *line, int max_width)
{
	char	*trimmed;
	char	*new_line;
	int		len;

	trimmed = ft_strtrim(line, " \t\r\n");
	if (!trimmed)
		return (NULL);
	len = ft_strlen(trimmed);
	new_line = malloc(sizeof(char) * (max_width + 1));
	if (!new_line)
	{
		free(trimmed);
		return (NULL);
	}
	copy_and_pad(new_line, trimmed, max_width);
	free(trimmed);
	return (new_line);
}

void	free_partial_map(char **map, int last_index)
{
	while (last_index-- >= 0)
		free(map[last_index]);
	free(map);
}

static int	fill_map_lines(char **map, char **lines, int h, int w)
{
	int	i;

	i = 0;
	while (i < h)
	{
		map[i] = process_map_line(lines[i], w);
		if (!map[i])
		{
			free_partial_map(map, i - 1);
			return (0);
		}
		i++;
	}
	map[h] = NULL;
	return (1);
}

int	parse_map(char **lines, t_config *cfg)
{
	int		h;
	int		w;
	char	**map;

	h = count_map_lines(lines);
	w = get_max_width(lines, h);
	map = malloc(sizeof(char *) * (h + 1));
	if (!map)
		return (0);
	if (!fill_map_lines(map, lines, h, w))
		return (0);
	cfg->map = map;
	cfg->map_height = h;
	cfg->map_width = w;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:02:32 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/09 18:33:12 by mcentell         ###   ########.fr       */
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
#include "cub3d.h"

static char	*process_map_line(char *line, int max_width)
{
	char	*trimmed;
	char	*new_line;
	int		len;
	int		j;

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
	j = 0;
	while (j < len)
	{
		new_line[j] = trimmed[j];
		j++;
	}
	while (j < max_width)
		new_line[j++] = ' ';
	new_line[max_width] = '\0';
	free(trimmed);
	return (new_line);
}

int	parse_map(char **lines, t_config *cfg)
{
	int		h = count_map_lines(lines);
	int		w = get_max_width(lines, h);
	int		i = 0;
	char	**map = malloc(sizeof(char *) * (h + 1));

	if (!map)
		return (0);
	while (i < h)
	{
		map[i] = process_map_line(lines[i], w);
		if (!map[i])
		{
			while (i-- >= 0)
				free(map[i]);
			free(map);
			return (0);
		}
		i++;
	}
	map[h] = NULL;
	cfg->map = map;
	cfg->map_height = h;
	cfg->map_width = w;
	return (1);
}


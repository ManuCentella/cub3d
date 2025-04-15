/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:03:37 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/14 12:14:13 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/inc/get_next_line.h"

static int	count_lines(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd); // ✅ avanzar a la siguiente línea
	}
	close(fd);
	return (count);
}


char	**read_cub_file(const char *filename)
{
	int		fd;
	int		lines_total;
	char	**lines;
	char	*line;
	int		i;

	lines_total = count_lines(filename);
	if (lines_total <= 0)
		return (NULL);
	lines = malloc(sizeof(char *) * (lines_total + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(lines), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

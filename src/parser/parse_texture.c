/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:31:26 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/10 18:05:09 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture_line(char *line, t_config *cfg)
{
	char	*trimmed;
	int		ret;

	ret = 0;
	printf("DEBUG LINE: \"%s\"\n", line);
	trimmed = ft_strtrim(line, " \t\r\n");
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		ret = assign_texture(&cfg->no_path, trimmed + 3, "NO");
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		ret = assign_texture(&cfg->so_path, trimmed + 3, "SO");
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		ret = assign_texture(&cfg->we_path, trimmed + 3, "WE");
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		ret = assign_texture(&cfg->ea_path, trimmed + 3, "EA");
	free(trimmed);
	return (ret);
}


static int	is_valid_texture_path(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (strcmp(path, ".") == 0 || strcmp(path, "..") == 0)
		return (0);
	if (len < 5 || strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	// Verifica que el archivo exista realmente
	// if (access(path, F_OK) != 0)
	// return (0);
	return (1);
}

int	assign_texture(char **dest, char *start, const char *id)
{
	while (*start == ' ')
		start++;
	if (*dest != NULL)
	{
		printf("Error\nDuplicate texture identifier: %s\n", id);
		return (0);
	}
	if (*start == '\0')
	{
		printf("Error\nEmpty texture path for identifier: %s\n", id);
		return (0);
	}
	if (!is_valid_texture_path(start))
	{
		printf("Error\nInvalid texture path for identifier: %s → \"%s\"\n", id,
			start);
		return (0);
	}
	*dest = ft_strdup(start);
	if (!*dest)
	{
		printf("Error\nFailed to allocate texture path for identifier: %s\n",
			id);
		return (0);
	}
	return (1);
}

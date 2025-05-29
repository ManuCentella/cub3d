/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:31:26 by mcentell          #+#    #+#             */
/*   Updated: 2025/05/28 16:55:43 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Valida duplicados, path no vacío y extensión .xpm.
 */
static int	check_texture_path_validity(t_config *cfg,
	char **dest, const char *path, const char *id)
{
	size_t len;

	if (*dest != NULL)
	{
		printf("Error\nDuplicate texture identifier: %s\n", id);
		cfg->error_already_reported = 1;
		return (0);
	}
	if (!path || path[0] == '\0')
	{
		printf("Error\nMissing texture path for identifier: %s\n", id);
		cfg->error_already_reported = 1;
		return (0);
	}
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		printf("Error\nInvalid texture path for identifier: %s → \"%s\"\n",
			   id, path);
		cfg->error_already_reported = 1;
		return (0);
	}
	return (1);
}

/*
 * Asigna la ruta (tras saltar espacios), llamando a la validación.
 */
int	assign_texture(t_config *cfg, char **dest, char *start, const char *id)
{
	while (*start == ' ')
		start++;
	if (!check_texture_path_validity(cfg, dest, start, id))
		return (0);
	*dest = ft_strdup(start);
	if (!*dest)
	{
		printf("Error\nFailed to allocate texture path for identifier: %s\n",
			   id);
		cfg->error_already_reported = 1;
		return (0);
	}
	return (1);
}

/*
 * Extrae el identificador NO/SO/WE/EA y llama a assign_texture.
 */
int	parse_texture_line(char *line, t_config *cfg)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_strtrim(line, " \t\r\n");
	if (!trimmed)
		return (0);
	ret = 0;
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		ret = assign_texture(cfg, &cfg->no_path, trimmed + 3, "NO");
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		ret = assign_texture(cfg, &cfg->so_path, trimmed + 3, "SO");
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		ret = assign_texture(cfg, &cfg->we_path, trimmed + 3, "WE");
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		ret = assign_texture(cfg, &cfg->ea_path, trimmed + 3, "EA");
	free(trimmed);
	return (ret);
}

/*
 * (Si lo usas en otro sitio, mantenlo; si no, ya no dará warning porque
 * se referencian en dispatch / assign.)
 */
int	parse_texture_path(char **path_ptr, char *line)
{
	while (*line == ' ')
		line++;
	if (*path_ptr != NULL)
	{
		printf("Error\nTexture identifier duplicated\n");
		return (0);
	}
	if (*line == '\0')
	{
		printf("Error\nMissing texture path\n");
		return (0);
	}
	*path_ptr = ft_strdup(line);
	if (!*path_ptr)
	{
		printf("Error\nMemory allocation failed\n");
		return (0);
	}
	return (1);
}

/*
 * Comprobación auxiliar independiente.
 */
int	is_valid_texture_path(const char *path)
{
	size_t len = ft_strlen(path);
	return (len >= 5 && ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:31:26 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/08 15:49:18 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int parse_texture_line(char *line, t_config *cfg)
{
    while(*line == ' ')
        line++;
    if (!ft_strncmp(line, "NO", 2) && line[2] == ' ')
        return(assign_texture(&cfg->no_path, line + 2));
    if (!ft_strncmp(line, "SO", 2) && line[2] == ' ')
        return(assign_texture(&cfg->so_path, line + 2));
    if (!ft_strncmp(line, "WE", 2) && line[2] == ' ')
        return(assign_texture(&cfg->we_path, line + 2));
    if (!ft_strncmp(line, "EA", 2) && line[2] == ' ')
        return(assign_texture(&cfg->ea_path, line + 2));
    return(0);
}

int	assign_texture(char **dest, char *start)
{
	while (*start == ' ')
		start++;
	if (*dest != NULL)
		return (0);
	*dest = ft_strdup(start);
	if (!(*dest))
		return (0);
	return (1);
}


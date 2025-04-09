/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dispathc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:09:50 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/09 14:27:38 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dispatch_parse_line(char *line, t_config *cfg)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (0); // línea vacía
	if ((line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		&& (line[1] == 'O' || line[1] == 'E' || line[1] == 'A')
		&& line[2] == ' ')
		return (parse_texture_line(line, cfg));
	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
		return (parse_color_line(line, cfg));
	return (0);
}

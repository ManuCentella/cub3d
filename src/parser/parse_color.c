/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:51:27 by mcentell          #+#    #+#             */
/*   Updated: 2025/05/26 18:50:23 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_rgb_component(const char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_and_validate_rgb(char **parts, int *r, int *g, int *b)
{
	*r = ft_atoi(parts[0]);
	*g = ft_atoi(parts[1]);
	*b = ft_atoi(parts[2]);
	if (!is_valid_rgb_component(parts[0]) || !is_valid_rgb_component(parts[1])
		|| !is_valid_rgb_component(parts[2]) || *r < 0 || *r > 255 || *g < 0
		|| *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	parse_rgb_values(char *str, int *r, int *g, int *b)
{
	char	**parts;
	int		count;
	int		success;

	parts = ft_split(str, ',');
	if (!parts)
		return (0);
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
		return (free_split(parts), 0);
	success = parse_and_validate_rgb(parts, r, g, b);
	free_split(parts);
	return (success);
}

int	parse_floor_color(char *rest, t_config *cfg)
{
	int	r;
	int	g;
	int	b;

	while (*rest == ' ')
		rest++;
	if (cfg->floor_color != -1)
	{
		printf("Error\nDuplicate floor color definition\n");
		return (0);
	}
	if (!parse_rgb_values(rest, &r, &g, &b))
		return (0);
	cfg->floor_color = (r << 16) | (g << 8) | b;
	return (1);
}

int	parse_ceiling_color(char *rest, t_config *cfg)
{
	int	r;
	int	g;
	int	b;

	while (*rest == ' ')
		rest++;
	if (cfg->ceiling_color != -1)
	{
		printf("Error\nDuplicate ceiling color definition\n");
		return (0);
	}
	if (!parse_rgb_values(rest, &r, &g, &b))
		return (0);
	cfg->ceiling_color = (r << 16) | (g << 8) | b;
	return (1);
}

int	parse_color_line(char *line, t_config *cfg)
{
	while (*line == ' ')
		line++;
	if (line[0] == 'F' && line[1] == ' ')
		return (parse_floor_color(line + 1, cfg));
	if (line[0] == 'C' && line[1] == ' ')
		return (parse_ceiling_color(line + 1, cfg));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:32:02 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/09 18:17:13 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/inc/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
}			t_config;

int			parse_texture_line(char *line, t_config *cfg);
int			assign_texture(char **dest, char *start);
int			parse_color_line(char *line, t_config *cfg);
int			parse_floor_color(char *rest, t_config *cfg);
int			parse_ceiling_color(char *rest, t_config *cfg);
void		free_split(char **arr);
int			dispatch_parse_line(char *line, t_config *cfg);
int			parse_config(char **lines, t_config *cfg, int *map_start);
int			find_map_start(char **lines, int start_index);
char		**read_cub_file(const char *filename);
int			is_config_complete(t_config *cfg);
int			parse_map(char **lines, t_config *cfg);
int			validate_config(t_config *cfg);
int			is_cell_closed(t_config *cfg, int y, int x);
char		get_map_cell(t_config *cfg, int y, int x);
int			is_valid_map_char(char c);
int			report_map_error(const char *msg, int *has_error);
void		validate_cell(t_config *cfg, int y, int x, int *player_count, int *has_error);
int			validate_map(t_config *cfg);

#endif

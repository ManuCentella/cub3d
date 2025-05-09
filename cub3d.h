/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:32:02 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/23 11:27:12 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.02
# define COLLIDE_RADIUS 0.1
# define DOOR_FRAME_DELAY  8
# define DOOR_FRAME_COUNT 7
# define NUM_TEXTURES (4 + DOOR_FRAME_COUNT)
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define MINIMAP_SCALE 15

# include "libft/inc/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_config
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
}				t_config;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	int			tex_num;
	int			tex_x;
	double		wall_x;

}				t_ray;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_texture
{
	void		*img;
	int			*data;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_texture;

typedef struct s_door
{
    int x;       // posición X de la puerta en el mapa
    int y;       // posición Y de la puerta en el mapa
    int state;   // 0=IDLE, 1=OPENING, 2=OPEN, 3=CLOSING
    int timer;   // índice de frame actual (0..DOOR_FRAME_COUNT‑1)
    int delay;   // contador interno para el retardo entre frames
    int entry_x; // posición X de la casilla desde donde se abrió la puerta
    int entry_y; // posición Y de la casilla desde donde se abrió la puerta
} t_door;



typedef enum e_tex_index
{
	TEX_NORTH = 0,
	TEX_SOUTH,
	TEX_EAST,
	TEX_WEST,
	TEX_DOOR_START, // TEX_DOOR_START..TEX_DOOR_START+DOOR_FRAME_COUNT-1
	TEX_COUNT = NUM_TEXTURES
}				t_tex_index;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_config	*config;
	t_player	player;
	t_image		image;
	t_keys		keys;
	t_texture	textures[NUM_TEXTURES];
	t_door		door;
}				t_game;

// handle_input.c
int				handle_keypress(int keycode, t_game *game);
int				handle_continuous_input(t_game *game);
int				key_release(int keycode, t_game *game);
int				key_press(int keycode, t_game *game);

// movement.c
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

/* render.c */
void			init_image(t_game *game);
void			put_pixel(t_image *img, int x, int y, int color);
void			render_frame(t_game *game);

/* raycast_logic.c */
void			calculate_ray_values(t_game *game, t_ray *ray, int x);
void			perform_dda(t_game *game, t_ray *ray);

/* raycast_draw.c */
void			compute_projection(t_game *game, t_ray *ray);
void			draw_column(t_game *game, t_ray *ray, int x);
void			init_player(t_game *game);
t_game			*init_game_window(t_config *cfg);
int				handle_keypress(int keycode, t_game *game);
int				close_window(t_game *game);
int				run_parser(t_config *cfg, const char *filename);
int				parse_texture_line(char *line, t_config *cfg);
int				assign_texture(char **dest, char *start, const char *id);
int				parse_color_line(char *line, t_config *cfg);
int				parse_floor_color(char *rest, t_config *cfg);
int				parse_ceiling_color(char *rest, t_config *cfg);
void			free_split(char **arr);
int				dispatch_parse_line(char *line, t_config *cfg);
int				parse_config(char **lines, t_config *cfg, int *map_start);
int				find_map_start(char **lines, int start_index);
char			**read_cub_file(const char *filename);
int				is_config_complete(t_config *cfg);
int				parse_map(char **lines, t_config *cfg);
int				validate_config(t_config *cfg);
int				is_cell_closed(t_config *cfg, int y, int x);
char			get_map_cell(t_config *cfg, int y, int x);
int				is_valid_map_char(char c);
int				report_map_error(const char *msg, int *has_error);
int				validate_map(t_config *cfg);
void			free_config(t_config *cfg);
void			free_map(char **map);
void			select_texture(t_ray *ray);
int				load_textures(t_game *game);
void			draw_minimap(t_game *game);
void			open_door(t_game *game);
void			update_door(t_game *game);
#endif

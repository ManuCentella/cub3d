# Nombre del ejecutable
NAME = cub3d

# Carpeta de objetos
OBJDIR = build

# Archivos fuente
SRCS = \
		src/game/main.c \
		src/game/init_mlx.c \
		src/game/render.c \
		src/game/movement.c\
		src/game/handle_input.c\
		src/game/raycast_logic.c\
		src/game/raycast_draw.c\
		src/game/init_player.c \
		src/parser/parse_texture.c \
		src/parser/parse_color.c \
		src/parser/parse_utils.c \
		src/parser/parse_config.c \
		src/parser/parse_dispathc.c \
		src/parser/read_cub_file.c \
		src/parser/parse_map.c \
		src/parser/validate_config.c \
		src/parser/maps_utils.c \
		src/parser/launch_parser.c\
		src/game/textures.c\
		src/game/minimap.c
# Archivos objeto con estructura en build/
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -Isrc -Iminilibx-linux

# Librería libft
LIBFT = libft/libft.a

# MiniLibX
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Regla principal
all: $(NAME)

# Cómo generar el ejecutable
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_FLAGS)

# Crear carpetas necesarias para build/
$(OBJDIR):
	mkdir -p $(OBJDIR)/src/parser
	mkdir -p $(OBJDIR)/src/game

# Regla general para compilar .c a .o dentro de build/
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar libft
$(LIBFT):
	make -C libft

# Compilar MiniLibX
$(MLX_LIB):
	make -C $(MLX_DIR)

# Limpieza de objetos
clean:
	make -C libft clean
	rm -rf $(OBJDIR)

# Limpieza total
fclean: clean
	make -C libft fclean
	rm -f $(NAME)

# Recompilar desde cero
re: fclean all

.PHONY: all clean fclean re

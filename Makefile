# Nombre del ejecutable
NAME = cub3d

# Carpeta de objetos
OBJDIR = build

# Archivos fuente
SRCS = parser_test.c \
		src/parser/parse_texture.c \
		src/parser/parse_color.c \
		src/parser/parse_utils.c\
		src/parser/parse_config.c\
		src/parser/parse_dispathc.c\
		src/parser/read_cub_file.c \
		src/parser/parse_map.c\
		src/parser/validate_config.c\
		src/parser/maps_utils.c

# Archivos objeto con estructura en build/
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -Isrc

# Librería libft
LIBFT = libft/libft.a

# Regla principal
all: $(NAME)

# Cómo generar el ejecutable
$(NAME): $(LIBFT) $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lm

# Crear carpeta build/ si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)/src/parser

# Regla general para compilar .c a .o dentro de build/
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar libft
$(LIBFT):
	make -C libft

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:40:41 by mcentell          #+#    #+#             */
/*   Updated: 2025/05/19 15:41:59 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	select_texture(t_ray *ray)
{
	if (ray->side == 0) // impacto vertical (E/W)
	{
		if (ray->ray_dir_x > 0)
			ray->tex_num = 2; // Este
		else
			ray->tex_num = 3; // Oeste
	}
	else // impacto horizontal (N/S)
	{
		if (ray->ray_dir_y > 0)
			ray->tex_num = 1; // Sur
		else
			ray->tex_num = 0; // Norte
	}
}

/*
 * Carga una imagen XPM y devuelve su buffer de píxeles.
 */
int *get_texture_data(void *mlx, const char *path, t_texture *tex)
{
    printf("Loading texture: %s\n", path);
    tex->img = mlx_xpm_file_to_image(mlx, (char *)path, &tex->width, &tex->height);
    if (!tex->img)
    {
        fprintf(stderr, "Error: could not load texture %s\n", path);
        return NULL;
    }
    return (int *)mlx_get_data_addr(
        tex->img,
        &tex->bpp,
        &tex->line_len,
        &tex->endian
    );
}
/*
 * Carga únicamente las 4 texturas de muro (NO, SO, EA, WE).
 */
int	load_textures(t_game *game)
{
	const char *wall_paths[4] = {
		game->config->no_path,
		game->config->so_path,
		game->config->ea_path,
		game->config->we_path
	};
	int	i = 0;

	while (i < 4)
	{
		game->textures[i].data = get_texture_data(
			game->mlx,
			(char *)wall_paths[i],
			&game->textures[i]
		);
		if (!game->textures[i].data)
			return 0;
		i++;
	}

	return 1;
}

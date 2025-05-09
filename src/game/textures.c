/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:40:41 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/22 19:23:13 by mcentell         ###   ########.fr       */
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

int	*get_texture_data(void *mlx, char *path, t_texture *tex)
{
	printf("Cargando textura: %s\n", path);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("❌ Error: no se pudo cargar la textura %s\n", path);
		return (NULL);
	}
	return ((int *)mlx_get_data_addr(tex->img, &tex->bpp,
				&tex->line_len, &tex->endian));
}


int load_textures(t_game *game)
{
    // Rutas de muros
    const char *wall_paths[4] = {
        game->config->no_path,
        game->config->so_path,
        game->config->ea_path,
        game->config->we_path
    };
    int i;
    // Carga texturas de muro
    for (i = 0; i < 4; i++)
    {
        game->textures[i].data = get_texture_data(game->mlx,
            (char *)wall_paths[i], &game->textures[i]);
        if (!game->textures[i].data)
            return (0);
    }
    // Carga texturas de puerta animada (door0.xpm ... door6.xpm)
    char path_buf[64];
    for (int f = 0; f < DOOR_FRAME_COUNT; f++)
    {
        snprintf(path_buf, sizeof(path_buf),
            "./textures/door%d.xpm", f);
        game->textures[TEX_DOOR_START + f].data =
            get_texture_data(game->mlx,
                path_buf,
                &game->textures[TEX_DOOR_START + f]
            );
        if (!game->textures[TEX_DOOR_START + f].data)
            return (0);
    }
    return (1);
}



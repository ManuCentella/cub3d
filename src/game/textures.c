/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:40:41 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/15 16:55:04 by mcentell         ###   ########.fr       */
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


int	load_textures(t_game *game)
{
	char	*paths[NUM_TEXTURES];
	int		i;

    paths[0] = game->config->no_path;
    paths[1] = game->config->so_path;
    paths[2] = game->config->ea_path;
    paths[3] = game->config->we_path;
    
	i = 0;
	while (i < NUM_TEXTURES)
	{
		game->textures[i].data = get_texture_data(game->mlx,
				paths[i], &game->textures[i]);
		if (!game->textures[i].data)
			return (0);
		i++;
	}
    if (!game->textures[i].data)
    {
	    printf("❌ Error: textura inválida o no cargada: %s\n", paths[i]);
	    return (0);
    }

	return (1);
}

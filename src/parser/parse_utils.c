/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:44:08 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/09 13:52:49 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **arr)
{
	int	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	is_config_complete(t_config *cfg)
{
	return (
		cfg->no_path &&
		cfg->so_path &&
		cfg->we_path &&
		cfg->ea_path &&
		cfg->floor_color != -1 &&
		cfg->ceiling_color != -1
	);
}

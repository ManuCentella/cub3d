/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:07:04 by mcentell          #+#    #+#             */
/*   Updated: 2025/04/28 10:50:06 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void open_door(t_game *game)
{
    int px = (int)game->player.x;
    int py = (int)game->player.y;

    if (game->door.state == 1)
        return;

    // guardamos la entrada
    game->door.entry_x = px;
    game->door.entry_y = py;

    if (game->config->map[py][px + 1] == 'D') {
        game->door.x = px + 1;  game->door.y = py;
    } else if (game->config->map[py][px - 1] == 'D') {
        game->door.x = px - 1;  game->door.y = py;
    } else if (game->config->map[py + 1][px] == 'D') {
        game->door.x = px;      game->door.y = py + 1;
    } else if (game->config->map[py - 1][px] == 'D') {
        game->door.x = px;      game->door.y = py - 1;
    } else {
        return;
    }

    game->door.state = 1;
    game->door.timer = 0;
    game->door.delay = 0;
}


void update_door(t_game *game)
{
    // OPENING (1)
    if (game->door.state == 1)
    {
        if (++game->door.delay < DOOR_FRAME_DELAY)
            return;
        game->door.delay = 0;
        if (++game->door.timer >= DOOR_FRAME_COUNT)
        {
            game->config->map[game->door.y][game->door.x] = '0';
            game->door.state = 2;            // pasa a OPEN
            game->door.timer = DOOR_FRAME_COUNT - 1;
        }
    }
    // OPEN (2): esperamos *hasta que el jugador salga* de la casilla
    else if (game->door.state == 2)
    {
        int px = (int)game->player.x;
        int py = (int)game->player.y;
        int ex = game->door.x   * 2 - game->door.entry_x;  // exit_x = 2*door.x - entry_x
        int ey = game->door.y   * 2 - game->door.entry_y;  // exit_y = 2*door.y - entry_y

        // si YA NO estamos en entry, ni en door, ni en exit → arrancar cierre
        if (!((px == game->door.entry_x && py == game->door.entry_y) ||
              (px == game->door.x       && py == game->door.y)       ||
              (px == ex                 && py == ey)))
        {
            game->door.state = 3;   // pasa a CLOSING
            game->door.delay = 0;
        }
    }
    // CLOSING (3)
    else if (game->door.state == 3)
    {
        if (++game->door.delay < DOOR_FRAME_DELAY)
            return;
        game->door.delay = 0;
        if (--game->door.timer < 0)
        {
            game->config->map[game->door.y][game->door.x] = 'D';
            game->door.state = 0;            // IDLE
            game->door.timer = 0;
            game->door.delay = 0;
        }
    }
    // IDLE (0): nada que hacer
}



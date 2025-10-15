/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:27:31 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/15 10:51:00 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/ft_printf.h"
#include "../libft/get_next_line.h"

typedef struct s_pos
{
	int x;
	int y;
}   t_pos;

typedef struct s_sprites
{
	void *player;
	void *wall;
	void *collectible;
	void *exit;
}   t_sprites;

typedef struct s_game
{
	char        **map;           // Mapa del juego
	int         map_width;       // Ancho del mapa
	int         map_height;      // Alto del mapa
	t_pos       player_init;     // Posición inicial del jugador
	t_pos       player_pos;      // Posición actual del jugador
	t_pos       prev_pos;        // Posición anterior del jugador
	int         collectibles;    // Número de coleccionables
	int         exits;           // Número de salidas
	int         moves;           // Contador de movimientos
	t_sprites   sprites;         // Sprites del juego

}   t_game;


#endif // SO_LONG_H


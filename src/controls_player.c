/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:35:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 00:06:29 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_player(t_game *g)
{
	int	player_x;
	int	player_y;

	player_x = g->player_pos.x * TILE;
	player_y = g->player_pos.y * TILE;
	if (!g->sprites.player)
		return ;
	if (g->player_instance >= 0
		&& (size_t)g->player_instance < g->sprites.player->count)
	{
		g->sprites.player->instances[g->player_instance].x = player_x;
		g->sprites.player->instances[g->player_instance].y = player_y;
	}
	else
		g->player_instance = mlx_image_to_window(
				g->mlx, g->sprites.player, player_x, player_y);
}

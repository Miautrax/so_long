/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_collect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:10:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:01:58 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	remove_collectible_instance(t_game *g, int px, int py)
{
	int	i;

	if (!g->sprites.collectible)
		return ;
	i = 0;
	while (i < (int)g->sprites.collectible->count)
	{
		if (g->sprites.collectible->instances[i].x == px
			&& g->sprites.collectible->instances[i].y == py)
		{
			g->sprites.collectible->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}

static void	reveal_exit_if_ready(t_game *g)
{
	int	y;
	int	x;

	if (g->collectibles != 0 || !g->sprites.exit)
		return ;
	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			if (g->map[y][x] == 'E')
			{
				x = x * TILE;
				y = y * TILE;
				mlx_image_to_window(g->mlx, g->sprites.exit, x, y);
			}
			x++;
		}
		y++;
	}
}

void	collect_if_needed(t_game *g, int x, int y)
{
	int	px;
	int	py;

	if (g->map[y][x] != 'C')
		return ;
	g->map[y][x] = '0';
	g->collectibles--;
	px = x * TILE;
	py = y * TILE;
	remove_collectible_instance(g, px, py);
	reveal_exit_if_ready(g);
}

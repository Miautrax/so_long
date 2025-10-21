/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_collect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:10:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 03:46:40 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	remove_collectible_instance(t_game *game, int px, int py)
{
	int	i;

	if (!game->sprites.collectible)
		return ;
	i = 0;
	while (i < (int)game->sprites.collectible->count)
	{
		if (game->sprites.collectible->instances[i].x == px
			&& game->sprites.collectible->instances[i].y == py)
		{
			game->sprites.collectible->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}

static void	reveal_exit_if_ready(t_game *game)
{
	int	y;
	int	x;

	if (game->collectibles != 0 || !game->sprites.exit)
		return ;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'E')
			{
				x = x * TILE;
				y = y * TILE;
				mlx_image_to_window(game->mlx, game->sprites.exit, x, y);
			}
			x++;
		}
		y++;
	}
}

void	collect_if_needed(t_game *game, int x, int y)
{
	int	px;
	int	py;

	if (game->map[y][x] != 'C')
		return ;
	game->map[y][x] = '0';
	game->collectibles--;
	px = x * TILE;
	py = y * TILE;
	remove_collectible_instance(game, px, py);
	reveal_exit_if_ready(game);
}

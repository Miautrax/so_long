/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:45:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 01:23:22 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_tile(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E')
		return (1);
	return (0);
}

static void	init_counts(t_game *game)
{
	game->collectibles = 0;
	game->exits = 0;
	game->player_init.x = -1;
	game->player_init.y = -1;
}

static void	visit_tile(t_game *game, int x, int y)
{
	char	c;

	c = game->map[y][x];
	if (c == 'P')
	{
		game->player_init.x = x;
		game->player_init.y = y;
	}
	else if (c == 'C')
		game->collectibles++;
	else if (c == 'E')
		game->exits++;
}

static int	scan_area(t_game *game, int *players)
{
	int		y;
	int		x;
	char	c;

	if (!game)
		return (0);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			c = game->map[y][x];
			if (!is_valid_tile(c))
				return (write(2, "Error\nInvalid char\n", 20), 0);
			if (c == 'P')
				(*players)++;
			visit_tile(game, x, y);
			x++;
		}
		y++;
	}
	return (1);
}

int	scan_tiles(t_game *game)
{
	int	players;

	if (!game)
		return (0);
	init_counts(game);
	players = 0;
	if (!scan_area(game, &players))
		return (0);
	if (players != 1)
		return (write(2, "Error\nPlayers must be 1\n", 22), 0);
	if (game->collectibles < 1)
		return (write(2, "Error\nNo collectibles\n", 22), 0);
	if (game->exits != 1)
		return (write(2, "Error\nExits must be 1\n", 20), 0);
	return (1);
}

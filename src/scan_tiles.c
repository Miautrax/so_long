/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:45:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:23:21 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_tile(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E')
		return (1);
	return (0);
}

static void	init_counts(t_game *g)
{
	g->collectibles = 0;
	g->exits = 0;
	g->player_init.x = -1;
	g->player_init.y = -1;
}

static void	visit_tile(t_game *g, int x, int y)
{
	char	c;

	c = g->map[y][x];
	if (c == 'P')
	{
		g->player_init.x = x;
		g->player_init.y = y;
	}
	else if (c == 'C')
		g->collectibles++;
	else if (c == 'E')
		g->exits++;
}

static int	scan_area(t_game *g, int *players)
{
	int		y;
	int		x;
	int		w;
	char	c;

	if (!g)
		return (0);
	y = 0;
	w = g->map_width;
	while (y < g->map_height)
	{
		x = 0;
		while (x < w)
		{
			c = g->map[y][x];
			if (!is_valid_tile(c))
				return (write(2, "Error\nInvalid char\n", 20), 0);
			if (c == 'P')
				(*players)++;
			visit_tile(g, x, y);
			x++;
		}
		y++;
	}
	return (1);
}

int	scan_tiles(t_game *g)
{
	int	players;

	if (!g)
		return (0);
	init_counts(g);
	players = 0;
	if (!scan_area(g, &players))
		return (0);
	if (players != 1)
		return (write(2, "Error\nPlayers must be 1\n", 22), 0);
	if (g->collectibles < 1)
		return (write(2, "Error\nNo collectibles\n", 22), 0);
	if (g->exits != 1)
		return (write(2, "Error\nExits must be 1\n", 20), 0);
	return (1);
}

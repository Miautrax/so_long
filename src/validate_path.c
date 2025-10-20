/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:20:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:50:02 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	finalize_marks(char **cp, int w, int h)
{
	int	y;
	int	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (cp[y][x] == 'v')
				cp[y][x] = 'V';
			x++;
		}
		y++;
	}
}

static int	spread_once(char **cp, int w, int h)
{
	int	chg;

	chg = expand_from(cp, w, h);
	finalize_marks(cp, w, h);
	return (chg);
}

static int	targets_ok(t_game *g, char **cp)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			if ((g->map[y][x] == 'C' || g->map[y][x] == 'E')
				&& cp[y][x] != 'V')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_path(t_game *g)
{
	char	**cp;
	int		y;
	int		x;

	cp = copy_map(g);
	if (!cp)
		return (write(2, "Error\nMalloc failed\n", 20), 0);
	y = g->player_init.y;
	x = g->player_init.x;
	cp[y][x] = 'V';
	while (spread_once(cp, g->map_width, g->map_height) > 0)
		;
	if (!targets_ok(g, cp))
	{
		write(2, "Error\nUnreachable path\n", 23);
		free_strarray_n(cp, g->map_height);
		return (0);
	}
	free_strarray_n(cp, g->map_height);
	return (1);
}

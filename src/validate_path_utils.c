/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:45:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:47:12 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(t_game *g)
{
	int		i;
	char	**cp;

	cp = (char **)malloc(sizeof(char *) * (g->map_height + 1));
	if (!cp)
		return (NULL);
	i = 0;
	while (i < g->map_height)
	{
		cp[i] = ft_strdup(g->map[i]);
		if (!cp[i])
			return (free_strarray_n(cp, i), NULL);
		i++;
	}
	cp[i] = NULL;
	return (cp);
}

static int	open_cell(char c)
{
	if (c == '0' || c == 'C' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

static int	expand_neighbors(char **cp, int y, int x, int *b)
{
	int	w;
	int	h;
	int	add;

	w = b[0];
	h = b[1];
	add = 0;
	if (y > 0 && open_cell(cp[y - 1][x]))
		cp[y - 1][x] = (add++, 'v');
	if (y + 1 < h && open_cell(cp[y + 1][x]))
		cp[y + 1][x] = (add++, 'v');
	if (x > 0 && open_cell(cp[y][x - 1]))
		cp[y][x - 1] = (add++, 'v');
	if (x + 1 < w && open_cell(cp[y][x + 1]))
		cp[y][x + 1] = (add++, 'v');
	return (add);
}

int	expand_from(char **cp, int w, int h)
{
	int	y;
	int	x;
	int	chg;
	int	bounds[2];
	int	inc;

	chg = 0;
	bounds[0] = w;
	bounds[1] = h;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (cp[y][x] == 'V')
			{
				inc = expand_neighbors(cp, y, x, bounds);
				chg += inc;
			}
			x++;
		}
		y++;
	}
	return (chg);
}

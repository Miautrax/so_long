/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:15:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:44:31 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	line_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static int	check_rows(t_game *g)
{
	int	i;
	int	w;
	int	h;
	int	len;

	i = 0;
	w = g->map_width;
	h = g->map_height;
	while (i < h)
	{
		len = line_len(g->map[i]);
		if (len != w)
			return (write(2, "Error\nNot rectangular\n", 23), 0);
		if (g->map[i][0] != '1' || g->map[i][w - 1] != '1')
			return (write(2, "Error\nOpen walls\n", 18), 0);
		i++;
	}
	return (1);
}

static int	check_top_bottom(t_game *g)
{
	int	i;
	int	w;
	int	h;

	i = 0;
	w = g->map_width;
	h = g->map_height;
	while (i < w)
	{
		if (g->map[0][i] != '1' || g->map[h - 1][i] != '1')
			return (write(2, "Error\nOpen walls\n", 18), 0);
		i++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!game || !game->map || game->map_height < 3 || game->map_width < 3)
		return (write(2, "Error\nMap too small\n", 20), 0);
	if (!check_rows(game))
		return (0);
	if (!check_top_bottom(game))
		return (0);
	if (!scan_tiles(game))
		return (0);
	return (1);
}

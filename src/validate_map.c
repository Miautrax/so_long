/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:15:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 02:43:01 by vboxuser         ###   ########.fr       */
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

static int	check_rows(t_game *game)
{
	int	i;
	int	map_width;
	int	map_height;
	int	len;

	i = 0;
	map_width = game->map_width;
	map_height = game->map_height;
	while (i < map_height)
	{
		len = line_len(game->map[i]);
		if (len != map_width)
			return (write(2, "Error\nNot rectangular\n", 23), 0);
		if (game->map[i][0] != '1' || game->map[i][map_width - 1] != '1')
			return (write(2, "Error\nOpen walls\n", 18), 0);
		i++;
	}
	return (1);
}

static int	check_top_bottom(t_game *game)
{
	int	i;
	int	map_width;
	int	map_height;

	i = 0;
	map_width = game->map_width;
	map_height = game->map_height;
	while (i < map_width)
	{
		if (game->map[0][i] != '1' || game->map[map_height - 1][i] != '1')
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

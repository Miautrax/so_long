/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:20:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 04:12:58 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	targets_ok(t_game *game, char **map_copy)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if ((game->map[y][x] == 'C' || game->map[y][x] == 'E')
				&& map_copy[y][x] != 'V')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_path(t_game *game)
{
	char	**map_copy;
	int		y;
	int		x;
	int		changes;

	map_copy = copy_map(game);
	if (!map_copy)
		return (write(2, "Error\nMalloc failed\n", 20), 0);
	y = game->player_init.y;
	x = game->player_init.x;
	map_copy[y][x] = 'V';
	changes = 1;
	while (changes > 0)
		changes = expand_from(map_copy, game->map_width, game->map_height);
	if (!targets_ok(game, map_copy))
	{
		write(2, "Error\nUnreachable path\n", 23);
		free_strarray_n(map_copy, game->map_height);
		return (0);
	}
	free_strarray_n(map_copy, game->map_height);
	return (1);
}

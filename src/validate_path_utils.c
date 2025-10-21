/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:45:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 04:18:04 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(t_game *game)
{
	int		i;
	char	**map_copy;

	map_copy = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
			return (free_strarray_n(map_copy, i), NULL);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static int	open_cell(char c)
{
	if (c == '0' || c == 'C' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

static int	expand_neighbors(char **map_copy, int y, int x, int *bounds)
{
	int	map_width;
	int	map_height;
	int	new_marks;

	map_width = bounds[0];
	map_height = bounds[1];
	new_marks = 0;
	if (y > 0 && open_cell(map_copy[y - 1][x]))
		map_copy[y - 1][x] = (new_marks++, 'V');
	if (y + 1 < map_height && open_cell(map_copy[y + 1][x]))
		map_copy[y + 1][x] = (new_marks++, 'V');
	if (x > 0 && open_cell(map_copy[y][x - 1]))
		map_copy[y][x - 1] = (new_marks++, 'V');
	if (x + 1 < map_width && open_cell(map_copy[y][x + 1]))
		map_copy[y][x + 1] = (new_marks++, 'V');
	return (new_marks);
}

int	expand_from(char **map_copy, int map_width, int map_height)
{
	int	y;
	int	x;
	int	total_new_marks;
	int	bounds[2];
	int	new_marks;

	total_new_marks = 0;
	bounds[0] = map_width;
	bounds[1] = map_height;
	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			if (map_copy[y][x] == 'V')
			{
				new_marks = expand_neighbors(map_copy, y, x, bounds);
				total_new_marks += new_marks;
			}
			x++;
		}
		y++;
	}
	return (total_new_marks);
}

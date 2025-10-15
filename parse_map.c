/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:54:52 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/15 11:22:59 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int  has_ber_extension(char *file)
{
    int i = 0;

    while (file[i])
        i++;
    if (i < 4)
        return (0);
    return (file[i - 4] == '.' && file[i - 3] == 'b'
        && file[i - 2] == 'e' && file[i - 1] == 'r');
}
static int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static int validate_and_prepare(char *file, t_game *game)
{
	if (!has_ber_extension(file))
		return (write(2, "Error\nInvalid file extension\n", 29), 0);
	game->map_height = count_lines(file);
	if (game->map_height == 0)
		return (write(2, "Error\nEmpty map\n", 16), 0);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		return (write(2, "Error\nMalloc failed\n", 20), 0);
	return (1);
}

static int load_map(char *file, t_game *game)
{
	int fd;
	int i;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nCould not open map file\n", 30), 0);
	i = 0;
	while ((line = get_next_line(fd)))
		game->map[i++] = line;
	game->map[i] = NULL;
	close(fd);
	game->map_width = 0;
	if (game->map_height > 0)
		while (game->map[0][game->map_width] && game->map[0][game->map_width] != '\n')
			game->map_width++;
	return (1);
}

int parse_map(char *file, t_game *game)
{
	if (!validate_and_prepare(file, game))
		return (0);
	if (!load_map(file, game))
		return (0);
	return (1);
}

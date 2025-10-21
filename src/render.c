/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:30:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 00:39:07 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	put_tile(mlx_image_t *img, t_game *game, int x, int y)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = x * TILE;
	pixel_y = y * TILE;
	return (mlx_image_to_window(game->mlx, img, pixel_x, pixel_y));
}

void	render_base(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			c = game->map[y][x];
			if (c == '1')
				put_tile(game->sprites.wall, game, x, y);
			else
				put_tile(game->sprites.floor, game, x, y);
			x++;
		}
		y++;
	}
}

void	render_overlays(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			c = game->map[y][x];
			if (c == 'C')
				put_tile(game->sprites.collectible, game, x, y);
			else if (c == 'E' && game->collectibles == 0)
				put_tile(game->sprites.exit, game, x, y);
			x++;
		}
		y++;
	}
}

void	place_player(t_game *game)
{
	if (game->sprites.player)
		game->player_instance = put_tile(game->sprites.player, game,
				game->player_init.x, game->player_init.y);
}

int	render_map(t_game *game)
{
	render_base(game);
	render_overlays(game);
	place_player(game);
	return (1);
}

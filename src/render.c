/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:30:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:19:19 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	put_tile(mlx_image_t *img, t_game *g, int x, int y)
{
	int	px;
	int	py;

	px = x * TILE;
	py = y * TILE;
	return (mlx_image_to_window(g->mlx, img, px, py));
}

void	render_base(t_game *g)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			c = g->map[y][x];
			if (c == '1')
				put_tile(g->sprites.wall, g, x, y);
			else
				put_tile(g->sprites.floor, g, x, y);
			x++;
		}
		y++;
	}
}

void	render_overlays(t_game *g)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < g->map_height)
	{
		x = 0;
		while (x < g->map_width)
		{
			c = g->map[y][x];
			if (c == 'C')
				put_tile(g->sprites.collectible, g, x, y);
			else if (c == 'E' && g->collectibles == 0)
				put_tile(g->sprites.exit, g, x, y);
			x++;
		}
		y++;
	}
}

void	place_player(t_game *g)
{
	if (g->sprites.player)
		g->player_instance = put_tile(g->sprites.player, g,
				g->player_init.x, g->player_init.y);
}

int	render_map(t_game *g)
{
	render_base(g);
	render_overlays(g);
	place_player(g);
	return (1);
}

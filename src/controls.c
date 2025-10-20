/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:00:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:07:29 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	can_step(t_game *g, int x, int y)
{
	if (x < 0 || y < 0 || x >= g->map_width || y >= g->map_height)
		return (0);
	if (g->map[y][x] == '1')
		return (0);
	return (1);
}

static void	try_move(t_game *g, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = g->player_pos.x + dx;
	ny = g->player_pos.y + dy;
	if (!can_step(g, nx, ny))
		return ;
	collect_if_needed(g, nx, ny);
	g->player_pos.x = nx;
	g->player_pos.y = ny;
	if (g->map[ny][nx] == 'E' && g->collectibles == 0)
		mlx_close_window(g->mlx);
	draw_player(g);
}

void	on_key(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(g->mlx);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		try_move(g, 0, -1);
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		try_move(g, 0, 1);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		try_move(g, -1, 0);
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		try_move(g, 1, 0);
}

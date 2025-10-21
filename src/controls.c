/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:00:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 00:09:03 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	can_step(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	if (game->map[y][x] == '1')
		return (0);
	return (1);
}

static void	try_move(t_game *game, int move_x, int move_y)
{
	int	new_x;
	int	new_y;

	new_x = game->player_pos.x + move_x;
	new_y = game->player_pos.y + move_y;
	if (!can_step(game, new_x, new_y))
		return ;
	collect_if_needed(game, new_x, new_y);
	game->player_pos.x = new_x;
	game->player_pos.y = new_y;
	if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
		mlx_close_window(game->mlx);
	draw_player(game);
}

void	on_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		try_move(game, 0, -1);
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		try_move(game, 0, 1);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		try_move(game, -1, 0);
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		try_move(game, 1, 0);
}

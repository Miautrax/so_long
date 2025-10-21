/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:05:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 03:07:07 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_game_struct(t_game *game)
{
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_init.x = -1;
	game->player_init.y = -1;
	game->player_pos = game->player_init;
	game->prev_pos = game->player_init;
	game->collectibles = 0;
	game->exits = 0;
	game->player_instance = -1;
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		mlx_status;

	if (argc != 2)
		return (write(2, "Usage: ./so_long <map.ber>\n", 28), 1);
	init_game_struct(&game);
	if (!parse_map(argv[1], &game))
		return (free_map(game.map), 1);
	mlx_status = init_mlx(&game);
	if (!mlx_status)
	{
		free_map(game.map);
		return (1);
	}
	render_map(&game);
	game.player_pos = game.player_init;
	mlx_key_hook(game.mlx, on_key, &game);
	mlx_loop(game.mlx);
	clear_loaded(&game);
	mlx_terminate(game.mlx);
	free_map(game.map);
	return (0);
}

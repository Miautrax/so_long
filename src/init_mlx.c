/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:25:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 02:53:42 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx(t_game *g)
{
	int	window_width;
	int	window_height;

	window_width = g->map_width * TILE;
	window_height = g->map_height * TILE;
	g->mlx = mlx_init(window_width, window_height, "so_long", false);
	if (!g->mlx)
		return (write(2, "Error\nMLX init failed\n", 21), 0);
	if (!create_images(g))
	{
		mlx_terminate(g->mlx);
		g->mlx = NULL;
		return (0);
	}
	return (1);
}

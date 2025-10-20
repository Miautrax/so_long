/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:25:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:08:09 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx(t_game *g)
{
	int	w;
	int	h;

	w = g->map_width * TILE;
	h = g->map_height * TILE;
	g->mlx = mlx_init(w, h, "so_long", false);
	if (!g->mlx)
		return (write(2, "Error\nMLX init failed\n", 21), 0);
	if (!create_images(g))
		return (0);
	return (1);
}

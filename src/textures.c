/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:45:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 01:29:48 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	del_img(mlx_t *mlx, mlx_image_t **img)
{
	if (!mlx || !img || !*img)
		return ;
	mlx_delete_image(mlx, *img);
	*img = NULL;
}

void	clear_loaded(t_game *g)
{
	if (!g || !g->mlx)
		return ;
	del_img(g->mlx, &g->sprites.floor);
	del_img(g->mlx, &g->sprites.wall);
	del_img(g->mlx, &g->sprites.player);
	del_img(g->mlx, &g->sprites.collectible);
	del_img(g->mlx, &g->sprites.exit);
}

static int	load_core_images(t_game *g)
{
	g->sprites.floor = load_png_scaled(g->mlx, "textures/Floor.png");
	if (!g->sprites.floor)
		return (write(2, "Error\nImage alloc failed\n", 24), 0);
	g->sprites.wall = load_png_scaled(g->mlx, "textures/Wall.png");
	if (!g->sprites.wall)
		return (
			clear_loaded(g),
			write(2, "Error\nImage alloc failed\n", 24),
			0);
	g->sprites.player = load_png_scaled(g->mlx, "textures/Player.png");
	if (!g->sprites.player)
		return (
			clear_loaded(g),
			write(2, "Error\nImage alloc failed\n", 24),
			0);
	return (1);
}

static int	load_extra_images(t_game *g)
{
	g->sprites.collectible = load_png_scaled(
			g->mlx, "textures/Collectible.png");
	if (!g->sprites.collectible)
		return (
			clear_loaded(g),
			write(2, "Error\nImage alloc failed\n", 24),
			0);
	g->sprites.exit = load_png_scaled(g->mlx, "textures/Exit.png");
	if (!g->sprites.exit)
		return (
			clear_loaded(g),
			write(2, "Error\nImage alloc failed\n", 24),
			0);
	return (1);
}

int	create_images(t_game *g)
{
	if (!load_core_images(g))
		return (0);
	if (!load_extra_images(g))
		return (0);
	return (1);
}

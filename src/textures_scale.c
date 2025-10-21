/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_scale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:45:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 01:28:21 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*load_png_scaled(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
		return (NULL);
	if (img->width != TILE || img->height != TILE)
		mlx_resize_image(img, TILE, TILE);
	return (img);
}

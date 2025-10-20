/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_scale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:45:00 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/20 22:26:55 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*load_png_scaled(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*tx;
	mlx_image_t		*img;

	tx = mlx_load_png(path);
	if (!tx)
		return (NULL);
	img = mlx_texture_to_image(mlx, tx);
	mlx_delete_texture(tx);
	if (!img)
		return (NULL);
	if (img->width != TILE || img->height != TILE)
		mlx_resize_image(img, TILE, TILE);
	return (img);
}

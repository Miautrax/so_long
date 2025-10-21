/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:27:31 by arivas-q          #+#    #+#             */
/*   Updated: 2025/10/21 04:17:26 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define TILE 48

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_sprites
{
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*floor;
}	t_sprites;

typedef struct s_game
{
	char		**map;
	int			map_width;
	int			map_height;
	t_pos		player_init;
	t_pos		player_pos;
	t_pos		prev_pos;
	int			collectibles;
	int			exits;
	int			player_instance;
	t_sprites	sprites;
	mlx_t		*mlx;
}	t_game;

/* Parsing / Validación */
int			parse_map(char *file, t_game *game);
int			validate_map(t_game *game);
int			validate_path(t_game *game);
int			scan_tiles(t_game *g);
char		**copy_map(t_game *g);
int			expand_from(char **cp, int map_width, int map_height);

/* MLX / Inicialización */
int			init_mlx(t_game *game);
int			create_images(t_game *game);
void		clear_loaded(t_game *game);
mlx_image_t	*load_png_scaled(mlx_t *mlx, const char *path);

/* Render / Controles */
int			render_map(t_game *game);
void		on_key(mlx_key_data_t keydata, void *param);
void		collect_if_needed(t_game *g, int x, int y);
void		draw_player(t_game *g);

/* Memoria */
void		free_map(char **map);
void		free_strarray_n(char **arr, int count);

#endif

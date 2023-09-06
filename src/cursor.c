/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:08:46 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:09:49 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_cursor(t_game *game)
{
	game->cursor.img.ptr = mlx_new_image(game->mlx_ptr, 60, 60);
	game->cursor.img.offset = mlx_get_data_addr(game->cursor.img.ptr, \
	&game->cursor.img.bits_per_pixel, &game->cursor.img.line_length, \
	&game->cursor.img.endian);
	game->cursor.hover = 0;
	game->cursor.shape = DOT;
	game->cursor.hover_x = 0;
	game->cursor.hover_y = 0;
}

void	print_shape(t_img *img, enum e_shape shape, int color, int pos[2])
{
	int	dist;

	my_mlx_pixel_put(img, pos[0], pos[1], trgb(255, 0, 0, 0));
	dist = ((30 - pos[0]) * (30 - pos[0])) + \
	((30 - pos[1]) * (30 - pos[1]));
	if (shape == CROSS && ((pos[0] >= 28 && pos[0] <= 32) \
	|| (pos[1] >= 28 && pos[1] <= 32)))
		my_mlx_pixel_put(img, pos[0], pos[1], color);
	if (shape == DOT && dist <= 36)
		my_mlx_pixel_put(img, pos[0], pos[1], color);
	if (shape == CIRCLE && dist <= 64 && dist >= 36)
		my_mlx_pixel_put(img, pos[0], pos[1], color);
}

void	print_sprite(t_img *img, int pos[2], int dimension[2], t_img *sprite)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 200)
	{
		j = -1;
		while (++j < 200)
		{
			my_mlx_pixel_put(img, i, j, trgb(255, 0, 0, 0));
			if (i <= dimension[0] && j <= dimension[1])
			{
				my_mlx_pixel_put(img, i, j, \
				get_texture_color(sprite, pos[0] + i, pos[1] + j));
			}
		}
	}
}

void	init_sprite(t_game *game)
{
	game->gun_sprite.ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/gun.xpm", &game->gun.width, &game->gun.height);
	game->gun_sprite.offset = mlx_get_data_addr(game->gun_sprite.ptr, \
	&game->gun_sprite.bits_per_pixel, &game->gun_sprite.line_length, \
	&game->gun_sprite.endian);
	game->gun.ptr = mlx_new_image(game->mlx_ptr, 200, 200);
	game->gun.offset = mlx_get_data_addr(game->gun.ptr, \
	&game->gun.bits_per_pixel, &game->gun.line_length, \
	&game->gun.endian);
	game->gun_sprite.width = 1024;
	game->gun_sprite.height = 1024;
	game->gun_effect[0].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/sprite_0.xpm", &game->gun.width, &game->gun.height);
	game->gun_effect[1].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/sprite_1.xpm", &game->gun.width, &game->gun.height);
	game->gun_effect[2].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/sprite_2.xpm", &game->gun.width, &game->gun.height);
	game->gun_effect[3].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/sprite_3.xpm", &game->gun.width, &game->gun.height);
	game->gun_effect[4].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/sprite_4.xpm", &game->gun.width, &game->gun.height);
	game->gun_effect[5].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/sprite_5.xpm", &game->gun.width, &game->gun.height);
	game->gun_effect[6].ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/sprite_6.xpm", &game->gun.width, &game->gun.height);
}

void	print_cursor(t_game *game, int i, int j)
{
	int	pos[2];

	while (++i < 60)
	{
		j = -1;
		while (++j < 60)
		{
			pos[0] = i;
			pos[1] = j;
			if (game->cursor.hover)
				print_shape(&game->cursor.img, game->cursor.shape, \
				trgb(0, 255, 1, 1), pos);
			else
				print_shape(&game->cursor.img, game->cursor.shape, \
				trgb(0, 1, 255, 1), pos);
		}
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->cursor.img.ptr, WIN_WIDTH_2 - 30, WIN_HEIGHT_2 - 30);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:18 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:19 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game2(t_game *game)
{
	game->down = 0;
	game->up = 0;
	game->left = 0;
	game->right = 0;
	game->should_cast = 1;
	game->mouse[0] = 0;
	game->mouse[1] = 0;
	game->hide_minimap = 0;
	game->color_type = 0;
	game->color_change = 0;
	game->dimension[0] = 140;
	game->dimension[1] = 200;
	game->pos[0][0] = 0;
	game->pos[0][1] = 0;
	game->pos[1][0] = 300;
	game->pos[1][1] = 0;
	game->pos[2][0] = 600;
	game->pos[2][1] = 0;
	game->firing = 0;
	game->fired = 0;
	game->key_d = 0;
	game->key_a = 0;
	game->mouse_lock = 1;
}

void	init_game(t_game *game, char *path)
{
	game->file = get_file_array(path);
	if (!game->file)
		terminate(NULL, "invalid map\n");
	game->map_allocated = 0;
	game->ea_path = get_path(game->file, EA);
	game->so_path = get_path(game->file, SO);
	game->we_path = get_path(game->file, WE);
	game->no_path = get_path(game->file, NO);
	if (!game->ea_path || !game->so_path || !game->we_path || !game->no_path)
		terminate(game, "error syntax texture\n");
	game->ceiling_color = get_color(game->file, CEILING);
	game->floor_color = get_color(game->file, FLOOR);
	if (game->ceiling_color == -1 || game->floor_color == -1)
		terminate(game, "Invalid color\n");
	game->map = get_map(game->file);
	if (!closed_map(game->map))
		terminate(game, "Invalid map\n");
	fill_map_blanks(game, game->map);
	init_game2(game);
}

void	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		terminate(game, "mlx_ptr error\n");
	game->win_ptr = \
	mlx_new_window(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cube_3D");
	if (game->win_ptr == NULL)
		terminate(game, "win_ptr error\n");
	game->player = malloc(sizeof(t_player));
	game->player->angle = get_init_angle(game);
	if (!set_player_position(game, -1, -1))
		terminate(game, "invalid number of players\n");
	add_doors(game, -1, -1);
	game->frame.ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	game->frame.offset = mlx_get_data_addr(game->frame.ptr, \
	&game->frame.bits_per_pixel, &game->frame.line_length, &game->frame.endian);
	game->minimap.ptr = mlx_new_image(game->mlx_ptr, 300, 300);
	game->minimap.offset = mlx_get_data_addr(game->minimap.ptr, \
	&game->minimap.bits_per_pixel, &game->minimap.line_length, \
	&game->minimap.endian);
	init_cursor(game);
	init_sprite(game);
	game->sprite_frame = 0;
	mlx_mouse_hide();
	mlx_mouse_move(game->win_ptr, WIN_WIDTH_2, WIN_HEIGHT_2);
	mlx_mouse_get_pos(game->win_ptr, &game->mouse[0], &game->mouse[1]);
}

void	init_asset_2(t_game *game)
{
	game->asset->we.ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	game->we_path, &game->asset->we.width, &game->asset->we.height);
	if (game->asset->we.ptr == NULL)
		terminate(game, "failed to load\n");
	game->asset->we.offset = mlx_get_data_addr(game->asset->we.ptr, \
	&game->asset->we.bits_per_pixel, &game->asset->we.line_length, \
	&game->asset->we.endian);
	game->asset->ea.ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	game->ea_path, &game->asset->ea.width, \
	&(game->asset->ea.height));
	if (game->asset->ea.ptr == NULL)
		terminate(game, "failed to load\n");
	game->asset->ea.offset = mlx_get_data_addr(game->asset->ea.ptr, \
	&game->asset->ea.bits_per_pixel, &game->asset->ea.line_length, \
	&game->asset->ea.endian);
	game->asset->d.ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	"ruins/door.xpm", &game->asset->d.width, \
	&(game->asset->d.height));
	if (game->asset->d.ptr == NULL)
		terminate(game, "failed to load\n");
	game->asset->d.offset = mlx_get_data_addr(game->asset->d.ptr, \
	&game->asset->d.bits_per_pixel, &game->asset->d.line_length, \
	&game->asset->d.endian);
}

void	init_asset(t_game *game)
{
	game->asset = malloc(sizeof(t_asset));
	if (game->asset == NULL)
		terminate(game, "");
	game->asset->d.ptr = NULL;
	game->asset->ea.ptr = NULL;
	game->asset->so.ptr = NULL;
	game->asset->no.ptr = NULL;
	game->asset->we.ptr = NULL;
	game->asset->no.ptr = mlx_xpm_file_to_image(game->mlx_ptr, game->no_path, \
	&game->asset->no.width, &game->asset->no.height);
	if (game->asset->no.ptr == NULL)
		terminate(game, "failed to load\n");
	game->asset->no.offset = mlx_get_data_addr(game->asset->no.ptr, \
	&game->asset->no.bits_per_pixel, &game->asset->no.line_length, \
	&game->asset->no.endian);
	game->asset->so.ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	game->so_path, &game->asset->so.width, &game->asset->so.height);
	if (game->asset->so.ptr == NULL)
		terminate(game, "failed to load\n");
	game->asset->so.offset = mlx_get_data_addr(game->asset->so.ptr, \
	&game->asset->so.bits_per_pixel, &game->asset->so.line_length, \
	&game->asset->so.endian);
	init_asset_2(game);
}

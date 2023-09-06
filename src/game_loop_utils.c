/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:13 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:17 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_mouse(t_game *game)
{
	int		mouse[2];
	double	diff;

	mlx_mouse_get_pos(game->win_ptr, &mouse[0], &mouse[1]);
	diff = mouse[0] - game->mouse[0];
	if (!diff)
		return (0);
	game->player->angle += diff / WIN_WIDTH_2;
	if (game->player->angle > M_PI * 2)
		game->player->angle -= M_PI * 2;
	if (game->player->angle < 0)
		game->player->angle += M_PI * 2;
	if (game->mouse_lock)
		mlx_mouse_move(game->win_ptr, WIN_WIDTH_2, WIN_HEIGHT_2);
	mlx_mouse_get_pos(game->win_ptr, &game->mouse[0], &game->mouse[1]);
	return (1);
}

void	raycast(t_game *game)
{
	t_ray	ray;

	ray.texture_offset = 0;
	ray.texture = 0;
	ray.x = game->player->x;
	ray.y = game->player->y;
	ray.x0 = game->player->x;
	ray.y0 = game->player->y;
	ray.angle = game->player->angle;
	if (!ray.angle || ray.angle == M_PI_2 || \
	ray.angle == M_PI || ray.angle == (M_PI_2 * 3))
		ray.angle += 0.001;
	ray.dx = cos(ray.angle);
	ray.dx_inv = 1 / cos(ray.angle);
	ray.dy = sin(ray.angle);
	ray.dy_inv = 1 / sin(ray.angle);
	build_frame(&ray, game);
	print_cursor(game, -1, -1);
	shoot(game);
}

int	change_color(t_game *game)
{
	if (!game->color_change)
		return (0);
	game->color_type++;
	if (game->color_type == 1)
		game->ceiling_color = trgb(0, 0, 0, 255);
	else if (game->color_type == 2)
		game->ceiling_color = trgb(0, 255, 0, 0);
	else if (game->color_type == 3)
		game->ceiling_color = trgb(0, 0, 255, 0);
	else
		game->ceiling_color = get_color(game->file, CEILING);
	if (game->color_type == 1)
		game->floor_color = trgb(0, 0, 255, 0);
	else if (game->color_type == 2)
		game->floor_color = trgb(0, 0, 0, 255);
	else if (game->color_type == 3)
		game->floor_color = trgb(0, 255, 0, 0);
	else
		game->floor_color = get_color(game->file, FLOOR);
	if (game->color_type > 3)
		game->color_type = 0;
	return (1);
}

void	input_ad(t_game *game)
{
	double	d_x;
	double	d_y;
	double	d_a;

	d_a = M_PI_2 + game->player->angle;
	d_x = cos(d_a) / 10;
	d_y = sin(d_a) / 10;
	if (game->key_a)
	{
		if (!is_wall(game->map, game->player->x + (3 * d_x), game->player->y))
			game->player->x += d_x;
		if (!is_wall(game->map, game->player->x, game->player->y + (3 * d_y)))
			game->player->y += d_y;
	}
	if (game->key_d)
	{
		d_x = -d_x;
		d_y = -d_y;
		if (!is_wall(game->map, game->player->x + (3 * d_x), game->player->y))
			game->player->x += d_x;
		if (!is_wall(game->map, game->player->x, game->player->y + (3 * d_y)))
			game->player->y += d_y;
	}
}

int	input_management(t_game *game, double d_x, double d_y)
{
	if (game->up || game->down || game->key_d || game->key_a)
	{
		d_x = cos(game->player->angle) / 10;
		d_y = sin(game->player->angle) / 10;
	}
	else if (!game->right && !game->left)
		return (0);
	if (game->up && !is_wall(game->map, game->player->x + \
	(d_x * 3), game->player->y))
		game->player->x += d_x;
	if (game->up && !is_wall(game->map, game->player->x, \
	game->player->y + (d_y * 3)))
		game->player->y += d_y;
	if (game->down && !is_wall(game->map, game->player->x - \
	(d_x * 3), game->player->y))
		game->player->x -= d_x;
	if (game->down && !is_wall(game->map, game->player->x, \
	game->player->y - (d_y * 3)))
		game->player->y -= d_y;
	if (game->left)
		game->player->angle += 0.05;
	if (game->right)
		game->player->angle -= 0.05;
	input_ad(game);
	return (1);
}

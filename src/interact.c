/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:20 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:20 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_tic(t_game *game, int tic)
{
	game->sprite_frame++;
	if (game->sprite_frame > 6)
		game->sprite_frame = 0;
	if ((game->sprite_frame % 2) && ++tic > 2)
	{
		if (game->firing)
			game->firing--;
		if (!game->firing)
			game->should_cast = 1;
		return (0);
	}
	return (tic);
}

int	get_state(int state)
{
	if (!state)
		return (15);
	else if (state == 5)
		return (-15);
	return (0);
}

void	interact(t_game *game, int i, int j)
{
	double	dist;

	game->fired = 0;
	game->cursor.hover = 0;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			dist = ((game->player->x - i) * (game->player->x - i)) + \
			((game->player->y - j) * (game->player->y - j));
			if (game->map[i][j] == 'O' && dist > 9)
				game->map[i][j] = 'C';
			if (i == game->cursor.hover_x && j == game->cursor.hover_y)
				game->map[i][j] = 'O';
		}
	}
}

int	animate_sprite(t_game *game, int tic)
{
	tic = get_tic(game, tic);
	if (game->firing)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
			game->gun_effect[game->sprite_frame].ptr, WIN_WIDTH_2, \
			WIN_HEIGHT - 180);
	else
		game->fired = 1;
	print_sprite(&game->gun, game->pos[tic], game->dimension, \
		&game->gun_sprite);
	return (tic);
}

void	shoot(t_game *game)
{
	static int	tic;
	static int	state;
	static int	clock;

	clock++;
	if ((game->down || game->up || state) && !(clock % 6))
		state = get_state(state);
	if (!game->firing)
		print_sprite(&game->gun, game->pos[tic], game->dimension, \
		&game->gun_sprite);
	else
		tic = animate_sprite(game, tic);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->gun.ptr, \
	WIN_WIDTH_2 - 40, WIN_HEIGHT - 200 + state);
	if (game->cursor.hover && game->firing && game->fired)
		interact(game, -1, -1);
	else
		game->cursor.hover = 0;
}

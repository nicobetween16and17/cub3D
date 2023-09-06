/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:34 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:34 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_gun_effect(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[0].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[1].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[2].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[3].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[4].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[5].ptr);
	mlx_destroy_image(game->mlx_ptr, game->gun_effect[6].ptr);
}

void	free_img(t_game *game)
{
	if (game->asset != NULL)
	{
		if (game->asset->d.ptr)
			mlx_destroy_image(game->mlx_ptr, game->asset->d.ptr);
		if (game->asset->ea.ptr)
			mlx_destroy_image(game->mlx_ptr, game->asset->ea.ptr);
		if (game->asset->no.ptr)
			mlx_destroy_image(game->mlx_ptr, game->asset->no.ptr);
		if (game->asset->we.ptr)
			mlx_destroy_image(game->mlx_ptr, game->asset->we.ptr);
		if (game->asset->so.ptr)
			mlx_destroy_image(game->mlx_ptr, game->asset->so.ptr);
	}
	if (game->minimap.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->minimap.ptr);
	if (game->player != NULL)
		free(game->player);
	if (game->gun_effect[0].ptr != NULL)
		free_gun_effect(game);
	if (game->gun.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->gun.ptr);
	if (game->gun_sprite.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->gun_sprite.ptr);
	if (game->frame.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->frame.ptr);
}

void	free_path(t_game *game)
{
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->ea_path)
		free(game->ea_path);
	if (game->we_path)
		free(game->we_path);
}

void	terminate(t_game *game, char *msg)
{
	if (game && game->mlx_ptr && game->win_ptr)
	{
		if (game->map_allocated)
			free_array(game->map);
		else
			free(game->map);
		free_path(game);
		free_array(game->file);
		free_img(game);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	}
	if (msg == NULL)
		exit(0);
	else
	{
		ft_putstr_fd("Error\n\t", 2);
		ft_putstr_fd(msg, 2);
		exit(1);
	}
}

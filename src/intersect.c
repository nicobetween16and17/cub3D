/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:21 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:21 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* check if current tile contain an element
 * copy tmp ray into ray
 * retreive the corresponding texture pointer and offest
 * slight differences between the 2 function depending 
 * on the direction of the ray
 */
int	intersect_we(t_ray *ray, t_ray *ray_tmp, t_game *game, char tile)
{
	tile = (game->map)[(int)(ray_tmp->x)][(int)(ray_tmp->y)];
	if (tile == '1')
	{
		ray_copy(ray_tmp, ray);
		ray->texture = &(game->asset->we);
		ray->texture_offset = ray->y - floor(ray->y);
		return (1);
	}
	if (tile == 'C')
	{
		if (game->current_ray >= WIN_WIDTH_2 - 25 && \
		game->current_ray <= WIN_WIDTH_2 + 25)
		{
			game->cursor.hover = 1;
			game->cursor.hover_x = (int)(ray_tmp->x);
			game->cursor.hover_y = (int)(ray_tmp->y);
		}
		ray_copy(ray_tmp, ray);
		ray->texture = &(game->asset->d);
		ray->texture_offset = ray->y - floor(ray->y);
		return (1);
	}
	return (0);
}

int	intersect_ea(t_ray *ray, t_ray *ray_tmp, t_game *game, char tile)
{
	tile = (game->map)[(int)(ray_tmp->x - 1)][(int)(ray_tmp->y)];
	if (tile == '1')
	{
		ray_copy(ray_tmp, ray);
		ray->texture = &(game->asset->ea);
		ray->texture_offset = ray->y - floor(ray->y);
		return (1);
	}
	if (tile == 'C')
	{
		if (game->current_ray >= WIN_WIDTH_2 - 25 && \
		game->current_ray <= WIN_WIDTH_2 + 25)
		{
			game->cursor.hover = 1;
			game->cursor.hover_x = (int)(ray_tmp->x - 1);
			game->cursor.hover_y = (int)(ray_tmp->y);
		}
		ray_copy(ray_tmp, ray);
		ray->texture = &(game->asset->d);
		ray->texture_offset = ray->y - floor(ray->y);
		return (1);
	}
	return (0);
}

int	intersect_no(t_ray *ray, t_ray *ray_tmp, t_game *game, char tile)
{
	tile = (game->map)[(int)(ray_tmp->x)][(int)(ray_tmp->y - 1)];
	if (tile == '1')
	{
		ray_copy(ray_tmp, ray);
		ray->texture = &(game->asset->no);
		ray->texture_offset = ray->x - floor(ray->x);
		return (1);
	}
	if (tile == 'C')
	{
		if (game->current_ray >= WIN_WIDTH_2 - 25 && \
		game->current_ray <= WIN_WIDTH_2 + 25)
		{
			game->cursor.hover = 1;
			game->cursor.hover_x = (int)(ray_tmp->x);
			game->cursor.hover_y = (int)(ray_tmp->y - 1);
		}
		ray_copy(ray_tmp, ray);
		ray->texture = &(game->asset->d);
		ray->texture_offset = ray->x - floor(ray->x);
		return (1);
	}
	return (0);
}

int	intersect_so(t_ray *ray, t_ray *ray_tmp, t_game *game, char tile)
{
	tile = (game->map)[(int)(ray_tmp->x)][(int)(ray_tmp->y)];
	if (tile == '1')
	{
		ray_copy(ray_tmp, ray);
		ray->texture = &(game->asset->so);
		ray->texture_offset = ray->x - floor(ray->x);
		return (1);
	}
	if (tile == 'C')
	{
		if (game->current_ray >= WIN_WIDTH_2 - 25 && \
		game->current_ray <= WIN_WIDTH_2 + 25)
		{
			game->cursor.hover = 1;
			game->cursor.hover_x = (int)(ray_tmp->x);
			game->cursor.hover_y = (int)(ray_tmp->y);
		}
		ray_copy(ray_tmp, ray);
		ray->texture = &(game->asset->d);
		ray->texture_offset = ray->x - floor(ray->x);
		return (1);
	}
	return (0);
}

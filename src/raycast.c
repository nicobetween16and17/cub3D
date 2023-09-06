/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:29 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:31 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_copy(t_ray *src, t_ray *dest)
{
	ft_memcpy(dest, src, sizeof(t_ray));
}

//////////////////////////////////////////////////////////////
/* move ray->x or ray->y to the next intersection with a tile
 * and update other values of the ray
 */
void	move_ray_x(t_ray *ray)
{
	if (ray->dx > 0)
		ray->x = ceil(ray->x + 0.000001);
	else if (ray->dx < 0)
		ray->x = floor(ray->x - 0.000001);
	ray->distance = (ray->x - ray->x0) * ray->dx_inv;
	ray->y = (ray->distance * ray->dy) + ray->y0;
}

void	move_ray_y(t_ray *ray)
{
	if (ray->dy > 0)
		ray->y = ceil(ray->y + 0.000001);
	else if (ray->dy < 0)
		ray->y = floor(ray->y - 0.000001);
	ray->distance = (ray->y - ray->y0) * ray->dy_inv;
	ray->x = (ray->distance * ray->dx) + ray->x0;
}

/* use two tmp rays 
 * cast one toward the next vertical intersection with a tile
 * the other toward the next horizontal intersection
 * check if tile is an asset
 * repeat until it finds a asset that stop the ray
 */
void	cast_ray(t_ray *ray, t_game *game)
{
	t_ray	ray_x;
	t_ray	ray_y;

	ray_copy(ray, &ray_x);
	ray_copy(ray, &ray_y);
	move_ray_x(&ray_x);
	move_ray_y(&ray_y);
	while (1)
	{
		if (ray_x.distance <= ray_y.distance)
		{
			if ((ray->dx < 0 && intersect_ea(ray, &ray_x, game, 0)) || \
			intersect_we(ray, &ray_x, game, 0))
				return ;
		}
		else if ((ray->dy < 0 && intersect_no(ray, &ray_y, game, 0)) || \
			intersect_so(ray, &ray_y, game, 0))
			return ;
		if (ray_x.distance <= ray_y.distance)
			move_ray_x(&ray_x);
		else
			move_ray_y(&ray_y);
	}
}

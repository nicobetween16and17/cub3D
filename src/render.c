/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:32 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:32 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < WIN_WIDTH && x >= 0 && y < WIN_HEIGHT && y >= 0)
	{
		*(unsigned int *)(img->offset + \
		(y * img->line_length + x * (img->bits_per_pixel / 8))) \
		= color;
	}
}

unsigned int	get_texture_color(t_img *img, int x, int y)
{
	if (x < img->width && x >= 0 && y < img->height && y >= 0)
	{
		return (*(unsigned int *)(img->offset + \
		(y * img->line_length + x * (img->bits_per_pixel / 8))));
	}
	return (0);
}

/* player size = 1.8
 * wall size = 3
 */
void	print_ray_on_img(t_ray *ray, int x, int y, t_game *game)
{
	double	lim1;
	double	lim2;
	double	y_texture;
	double	y_incr;

	lim2 = WIN_HEIGHT_2 * (1 + (1.2 / ray->distance));
	lim1 = WIN_HEIGHT_2 * (1 - (2.8 / ray->distance));
	y_incr = (ray->texture->height / fabs(lim2 - lim1));
	y_texture = 0;
	if (lim1 < 0)
		y_texture = (lim1 * -1) * y_incr;
	while (++y < WIN_HEIGHT)
	{
		if (y < lim1)
			my_mlx_pixel_put(&game->frame, x, y, game->ceiling_color);
		else if (y < lim2)
		{
			my_mlx_pixel_put(&game->frame, x, y, get_texture_color(\
ray->texture, (int)(ray->texture_offset * ray->texture->width) \
, (int)y_texture));
			y_texture += y_incr;
		}
		else
			my_mlx_pixel_put(&game->frame, x, y, game->floor_color);
	}
}

void	reset_ray(t_ray *ray, t_game *game)
{
	ray->distance = 0;
	ray->dx = cos(ray->angle);
	ray->dx_inv = 1 / cos(ray->angle);
	ray->dy = sin(ray->angle);
	ray->dy_inv = 1 / sin(ray->angle);
	ray->x = game->player->x;
	ray->y = game->player->y;
	ray->x0 = game->player->x;
	ray->y0 = game->player->y;
	ray->texture_offset = 0;
	ray->texture = 0;
}

void	*build_frame(t_ray *ray, t_game *game)
{
	int		i;
	double	angle_incr;
	double	fisheye_angle;

	i = 0;
	angle_incr = (M_PI_2) / WIN_WIDTH;
	fisheye_angle = -1 * M_PI_4 / 2;
	ray->angle -= M_PI_4;
	while (i < WIN_WIDTH)
	{
		game->current_ray = i;
		cast_ray(ray, game);
		ray->distance = ray->distance * cos(fisheye_angle);
		print_ray_on_img(ray, i, 0, game);
		ray->angle = ray->angle + angle_incr;
		fisheye_angle = fisheye_angle + angle_incr / 2;
		reset_ray(ray, game);
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
					game->frame.ptr, 0, 0);
	return (NULL);
}

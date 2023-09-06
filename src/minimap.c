/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:23 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:23 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_charset(char c, char *set, int i)
{
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static char	**get_map2(char **file, int i, int j, int k)
{
	char	**map;

	map = malloc(sizeof(char *) * k);
	if (!map)
		return (NULL);
	while (file[++i])
	{
		k = 0;
		while (file[i][k] == ' ')
			k++;
		if (file[i][k] == '1')
			map[j++] = file[i];
	}
	map[j] = 0;
	return (map);
}

char	**get_map(char **file)
{
	int	i;
	int	j;
	int	k;

	j = 1;
	i = 0;
	while (file[++i])
	{
		k = 0;
		while (file[i][k] == ' ')
			k++;
		j += (file[i][k] == '1');
	}
	return (get_map2(file, 0, 0, j));
}

/*
 * Assign every pixel of the image to transparent
 * Then for each element of the map, print if it's nearby the player
 * the element is a square semi transparent, cut at the edges to fit in a circle
 * Then print the field of view noearby the player
 * Then print the player at the center of the minimap as a dot
 * Then print the image in the window
 */
void	minimap(t_game *game)
{
	t_img	minimap;
	int		i;
	int		j;

	i = -1;
	minimap = game->minimap;
	while (++i < 300)
	{
		j = -1;
		while (++j < 300)
			my_mlx_pixel_put(&minimap, i, j, trgb(255, 0, 0, 0));
	}
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
			print_element(&minimap, game, i, j);
	}
	print_player_fov(&minimap, game, trgb(128, 255, 255, 0));
	print_player(&minimap, 130, 130, trgb(128, 255, 100, 100));
	print_outer_circle(&minimap, 130, 65, trgb(0, 255, 255, 255));
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, minimap.ptr, 0, 0);
}

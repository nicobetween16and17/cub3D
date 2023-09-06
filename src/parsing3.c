/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:58:58 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 14:59:00 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	set_player_position(t_game *game, int i, int j)
{
	int	nb;
	int	ligne;
	int	colonne;

	nb = 0;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (is_charset(game->map[i][j], "NWES", -1) && ++nb)
			{
				colonne = j;
				ligne = i;
			}
		}
	}
	if (nb != 1)
		return (0);
	game->player->x = ligne + 0.5;
	game->player->y = colonne + 0.5;
	return (1);
}

double	get_init_angle(t_game *game)
{
	int		i;
	double	dir;

	dir = 0;
	i = -1;
	while (game->map[++i])
	{
		if (does_contain(game->map[i], 'S') || \
		(++dir && does_contain(game->map[i], 'E')) || \
		(++dir && does_contain(game->map[i], 'N')) || \
		(++dir && does_contain(game->map[i], 'W')))
			return ((M_PI_2 * dir));
		else
			dir = 0;
	}
	return (0);
}

int	get_color2(char **elements)
{
	int		int_color;
	char	**rgb;
	int		i;
	int		err;

	err = 0;
	int_color = 0;
	rgb = ft_split(elements[1], ',');
	(!rgb && ++err);
	if (!err && arr_size(rgb) != 3 && ++err)
		free_array(rgb);
	i = -1;
	while (!err && rgb[++i])
		if (!err && (ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0) && ++err)
			free_array(rgb);
	if (err)
		return (-1);
	int_color += ft_atoi(rgb[0]) << 16;
	int_color += (ft_atoi(rgb[1]) << 8) + ft_atoi(rgb[2]);
	free_array(rgb);
	return (int_color);
}

int	get_color(char **file, t_color color)
{
	int		i;
	int		int_color;
	char	*c_a;
	char	**elements;

	c_a = "C ";
	if (color == FLOOR)
		c_a = "F ";
	i = 0;
	while (file[i] && !str_in_str(file[i], c_a, ft_strlen(file[i])))
		i++;
	elements = ft_split(file[i], ' ');
	if (!elements)
		return (-1);
	if (arr_size(elements) != 2)
	{
		free_array(elements);
		return (-1);
	}
	if (!file[i] || !valid_format(elements[1]))
		return (-1);
	int_color = get_color2(elements);
	free_array(elements);
	return (int_color);
}

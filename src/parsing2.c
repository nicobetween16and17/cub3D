/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:26 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:28 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*add_spaces(char *line, size_t target_len)
{
	char	*tmp;
	size_t	i;

	i = -1;
	if (ft_strlen(line) < target_len)
	{
		tmp = malloc((int)target_len * sizeof(char));
		if (!tmp)
			return (NULL);
		while (line[++i])
			tmp[i] = line[i];
		while (i < target_len)
			tmp[i++] = 32;
		tmp[i] = 0;
		return (tmp);
	}
	else
		return (ft_strdup(line));
}

void	fill_map_blanks(t_game *game, char **map)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	game->map_allocated = 1;
	while (map[++i])
	{
		if (!valid_map_line(map[i]))
		{
			map[i] = 0;
			terminate(game, "Invalid map\n");
		}
		if (ft_strlen(map[i]) > j)
			j = ft_strlen(map[i]);
	}
	i = -1;
	while (game->map[++i])
	{
		game->map[i] = add_spaces(map[i], j);
		if (game->map[i] == NULL)
			terminate(game, "failed malloc\n");
	}
}

int	closed_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || map[i + 1] == 0 || j == 0 || map[i][j + 1] == 0)
					return (0);
				if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ' || \
				map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (0);
			}
		}
	}
	return (1);
}

int	is_hallway(char **map, int i, int j)
{
	return (i && map[i + 1] && j && map[i][j] == '0' && \
	((map[i + 1][j] == '0' && map[i - 1][j] == '0' && map[i][j + 1] == '1' \
	&& map[i][j - 1] == '1') || (map[i + 1][j] == '1' && map[i - 1][j] == '1' \
	&& map[i][j + 1] == '0' && map[i][j - 1] == '0')));
}

void	add_doors(t_game *game, int i, int j)
{
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'S' || game->map[i][j] == 'W' || \
			game->map[i][j] == 'E' || game->map[i][j] == 'N')
				game->map[i][j] = '0';
		}
	}
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (is_hallway(game->map, i, j) && \
			((!is_hallway(game->map, i - 1, j) && \
			!is_hallway(game->map, i + 1, j)) || \
			(!is_hallway(game->map, i, j -1) && \
			!is_hallway(game->map, i, j + 1))))
				game->map[i][j] = 'C';
		}
	}
}

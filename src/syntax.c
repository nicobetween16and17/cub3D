/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:33 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:33 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*str_in_str(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	i = 0;
	if (!ft_strlen(s2))
		return ((char *)s1);
	while (s1[i] != '\0' && s1[i] != '\n' && i < n)
	{
		j = 0;
		while (s2[j] && s2[j] == s1[i + j] && i + j < n)
		{
			j++;
			if (s2[j] == '\0')
				return (s1 + i);
		}
		i++;
	}
	return (0);
}

int	valid_format(char *s)
{
	int	i;
	int	nb;
	int	coma;

	i = -1;
	nb = 0;
	coma = 0;
	while (s[++i])
	{
		if (s[i] == ',' && !nb)
			return (0);
		(!nb && ft_isdigit(s[i]) && nb++);
		(s[i] == ',' && ++coma && nb--);
	}
	return (coma == 2);
}

int	is_invalid_name(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (1);
	while (s[++i])
	{
		if (s[i] == '.')
			break ;
	}
	return (ft_strcmp(s + i, ".cub"));
}

int	valid_map_line(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S' && \
		s[i] != 'E' && s[i] != 'W' && s[i] != ' ')
			return (0);
	}
	return (1);
}

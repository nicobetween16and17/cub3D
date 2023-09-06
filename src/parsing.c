/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:10:25 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:10:25 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_buffer_size(char *s)
{
	int		fd;
	char	tmp;
	int		tot;

	tot = 0;
	fd = open(s, O_RDONLY);
	if (fd < 0)
		terminate(NULL, "file does not exist\n");
	while (read(fd, &tmp, 1))
		tot++;
	close(fd);
	return (tot);
}

int	giga_check(char *buf, int buf_size)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		while (buf[i] && buf[i] == '\n')
			i++;
		if (!((str_in_str(buf + i, "NO ", buf_size) || str_in_str(buf + i, \
		"SO ", buf_size) || str_in_str(buf + i, "EA ", buf_size) || \
		str_in_str(buf + i, "WE ", buf_size) || str_in_str(buf + i, \
		"F ", buf_size) || str_in_str(buf + i, "C ", buf_size))))
			break ;
		while (buf[i] && buf[i] != '\n')
			i++;
	}
	while (buf[i] && buf[i] == '\n')
		i++;
	i -= 1;
	while (buf[++i])
	{
		if ((buf[i] == '\n' && i && buf[i - 1] == '\n') || \
		(!is_charset(buf[i], "01 NSWE\n", -1)))
			return (1);
	}
	return (0);
}

char	**get_file_array(char *s)
{
	char	**arr;
	int		fd;
	char	*buf;
	int		size;

	if (is_invalid_name(s))
		terminate(NULL, "invalid map name\n");
	size = get_buffer_size(s);
	buf = malloc(size + 1);
	if (buf == NULL)
		terminate(NULL, "failed malloc\n");
	fd = open(s, O_RDONLY);
	if (fd == -1)
		safe_free(buf);
	if (!buf)
		terminate(NULL, "no file\n");
	read(fd, buf, size);
	buf[size + 1] = 0;
	if (giga_check(buf, size))
		if (safe_free(buf))
			return (NULL);
	arr = ft_split(buf, '\n');
	safe_free(buf);
	return (arr);
}

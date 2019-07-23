/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midounhocine <midounhocine@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:15 by midounhoc         #+#    #+#             */
/*   Updated: 2019/04/25 15:52:36 by midounhocin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		search_end(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*read_file(char *str, int fd)
{
	int		ret;
	char	buffer[BUFF_SIZE + 1];
	char	*free_it;

	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		free_it = str;
		str = ft_strjoin(str, buffer);
		free(free_it);
		if (search_end(buffer) >= 0)
			break ;
	}
	return (str);
}

int		get_next_line(int const fd, char **line)
{
	static char	tmp[OPEN_MAX][BUFF_SIZE + 1];
	int			end;

	if (fd < 0 || !line || read(fd, tmp, 0) < 0 || fd > OPEN_MAX)
		return (-1);
	*line = ft_strdup(tmp[fd]);
	end = search_end(*line);
	if (end < 0)
	{
		*line = read_file(*line, fd);
		if (!**line)
			return (0);
		end = search_end(*line);
	}
	tmp[fd][0] = '\0';
	if (end >= 0)
	{
		ft_strcpy(tmp[fd], *line + end + 1);
		(*line)[end] = '\0';
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:15 by midounhoc         #+#    #+#             */
/*   Updated: 2019/04/21 18:27:35 by hmidoun          ###   ########.fr       */
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

	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		str = ft_strcat(str, buffer);
		if (search_end(buffer) >= 0)
			break ;
	}
	return (str);
}

int		get_next_line(int const fd, char **line)
{
	static char	tmp[BUFF_SIZE + 1];
	int			end;

	if (fd < 0 || !line || read(fd, tmp, 0) < 0)
		return (-1);
	*line = ft_strdup(tmp);
	end = search_end(*line);
	if (end < 0)
	{
		*line = read_file(*line, fd);
		if (!**line)
		{
			free(*line);
			*line = ft_strdup("");
			return (0);
		}
		end = search_end(*line);
	}
	*tmp = '\0';
	if (end >= 0)
	{
		ft_strcpy(tmp, *line + end + 1);
		(*line)[end] = '\0';
	}
	return (1);
}

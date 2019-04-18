/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:15 by midounhoc         #+#    #+#             */
/*   Updated: 2019/04/18 17:39:32 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			search_end(char *str)
{
	char *c;
	char *t;

	t = str;
	c = ft_strchr(str, '\n');
	if (c)
		return (c - str);
	return (-1);
}

char	*read_file(char *str, int fd)
{
	char	*tmp;
	int		ret;

	tmp =(char *)malloc(sizeof(char) * (BUFF_SIZE+2));
	ret = 1;
	if(!tmp)
		return(NULL);
	while (search_end(tmp) < 0 && ret > 0)
		{
			ret = read(fd, tmp, BUFF_SIZE);
			if (ret)
				tmp[ret] = '\0';
			str = ft_strjoin(str,tmp);
		}
	free(tmp);
	return(str);
}

int		get_next_line(int const fd, char **line)
{
	static char	*str;
	int			end;
	char c;

	if(fd < 0 || !(*line))
		return(-1);
	if(!str)
	{
		str = (char*)malloc(sizeof(char) * (BUFF_SIZE+1));
		if(!str)
			return(-1);
	}
/*
	while (*str == '\n')
		str++;*/
	str = read_file(str,fd);
	end = search_end(str);
	c = *str;
	if (*str < 0)
	{
		*line = NULL;
		return (0);
	}
	if (end >= 0)
	{
		*line = ft_strsub(str,0,end);
		str += end + 1;
	}
	return(1);
}

int main()
{


    int fd;
    int tst;
    char *line;

	fd = open("tst", O_RDONLY) ;
   line = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));

   for(int i= 0 ; i<12; i++)
   {
   	tst = get_next_line(fd,&line);

   //line = read_file(line,fd);

  printf("%s",line);
   }
  return(0);
}


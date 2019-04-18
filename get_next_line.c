/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:15 by midounhoc         #+#    #+#             */
/*   Updated: 2019/04/18 18:23:10 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			search_end(char *str)
{
	char *c;
	char *t;

	c = ft_strchr(str, '\n');
	if (c)
		return (c - str);
	return (-1);
}

int		get_next_line(int const fd, char **line)
{
	static char	*str;
	int			end;
	int			ret;

	ret = 1;
	if(!str)
		str = (char*)malloc(sizeof(char) * (BUFF_SIZE+1));
	if(fd < 0 || !(*line) || !str)
		return(-1);
	if ((end = search_end(str)) < 0)
	{
		*line = ft_strsub(str, 0, ft_strlen(str));
		str += ft_strlen(str);
	}
	else
	{
		*line = ft_strsub(str, 0, end);
		str += end;
		return (1);
	}

	while (ret > 0)
	{
		ret = read(fd, str, BUFF_SIZE);
		str[ret] = '\0';
		*line = ft_strjoin(*line,str);
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

  printf("%s\n\t%d\t**************************************************** %d\n",line,tst,i);
   }
  return(0);
}


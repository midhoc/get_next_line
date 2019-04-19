/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:15 by midounhoc         #+#    #+#             */
/*   Updated: 2019/04/19 23:08:40 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		search_end(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\n')
			return(i);
		i++;
	}
	return(-1);
}

char	*read_file(char *str, int fd)
{
	char	*tmp;
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	while ( (ret = read(fd, buffer, BUFF_SIZE)) > 0)
		{
			buffer[ret] = '\0';
			tmp = ft_strdup(str);
			ft_strdel(&str);
			str = ft_strjoin(tmp,buffer);
			free(tmp);
			if (search_end(buffer) >= 0)
				break;
		}
	return(str);
}

int		get_next_line(int const fd, char **line)
{
	static char	*str;
	int			end;

	if(!str)
		str = (char*)malloc(sizeof(char) * (BUFF_SIZE+1));
	if(!str || fd < 0 || !line)
		return(-1);
	end = search_end(str);
	if (end < 0)
	{
		if (!(str = read_file(str,fd)))
			return (-1);
		if (!*str)
		{
			*line = ft_strdup("");
			return (0);
		}
		end = search_end(str);
	}
	if (end < 0)
	{
		*line = ft_strdup( str);
		*str = '\0';
	}
	else
	{
		*line = ft_strsub(str,0,end);
		str += 1+end;
	}
	return(1);
}

int main()
{
    int fd = open("/Users/hmidoun/gnl/tst/gnl1_2.txt", O_RDONLY) ;
   int tst;

    char *line;

   //line = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));

   for(int i= 0 ; i<2; i++)
   {
   tst = get_next_line(fd,&line);

  printf("%s\n",line);
   }
  return(0);
}


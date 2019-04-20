/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midounhocine <midounhocine@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:15 by midounhoc         #+#    #+#             */
/*   Updated: 2019/04/20 20:49:24 by midounhocin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		search_end(char *str)
{
	int i;

	i = 0;
	while(str && str[i])
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
			if(str != NULL)
			{
				tmp = ft_strdup(str);
				free(str);
			}
			else
				tmp = ft_strdup("");
			str = ft_strjoin(tmp,buffer);
			free(tmp);
			if (search_end(buffer) >= 0)
				break;
		}
	return(str);
}

int		get_next_line(int const fd, char **line)
{
	char	*str;
	static char				tmp[BUFF_SIZE + 1];
	int			end;

	if (*tmp)
			str = ft_strdup(tmp);
	else
		str = ft_strdup("");
	if(fd < 0 || !line || read(fd, str, 0) < 0)
		return(-1);
	end = search_end(str);
	if (end < 0)
	{
		str = read_file(str,fd);
			//return (-1);
		if (!*str)
		{
			*line = ft_strdup("");
			free(str);
			return (0);
		}
		end = search_end(str);
	}
	if (end < 0)
	{
		*line = ft_strdup(str);
		free(str);
		*tmp = '\0';
	}
	else
	{
		*line = ft_strsub(str,0,end);
		ft_strcpy(tmp, str+end+1);
		//str += 1+end;
		free(str);
	}
	//ft_strdel(&str);
	return(1);
}
/*
int main()
{
    int fd = open("/Users/midounhocine/get_next_line/gnl1_2.txt", O_RDONLY) ;
   int tst;

    char *line;

   //line = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));

   for(int i= 0 ; i<12; i++)
   {
   tst = get_next_line(fd,&line);

  printf("%s\n \t %d\t%d\n",line,tst,i);
   }
  return(0);
}
*/
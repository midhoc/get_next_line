/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midounhocine <midounhocine@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:15 by midounhoc         #+#    #+#             */
/*   Updated: 2019/04/19 00:27:18 by midounhocin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		search_end(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\n' || str[i] == -1)
			return(i);
		i++;
	}
	return(-1);
}

char	*read_file(char *str, int fd)
{
	char	*tmp;
	int		ret;

	tmp =(char *)malloc(sizeof(char) * (BUFF_SIZE+2));
	if(!tmp)
		return(NULL);
	while ((ret = read(fd, tmp, BUFF_SIZE)) > 0 )
		{
			tmp[ret] = '\0';
			str = ft_strjoin(str,tmp);
			if(search_end(tmp) >= 0)
				break;
		}
	if (ret == 0)
		{
			str[ft_strlen(str)] = -1;
			str[ft_strlen(str)] = '\n';
		}
	free(tmp);
	return(str);
}

int		get_next_line(int const fd, char **line)
{
	static char	*str;
	int			end;

	if(!str)
		str = (char*)malloc(sizeof(char) * (BUFF_SIZE+1));
	if(!str || fd < 0 || !(*line))
		return (-1);
if(*str == -1)
	{
		*line = NULL;
		return(0);
	}
	end = search_end(str);
	if (end < 0)
		str = read_file(str,fd);
	
	end = search_end(str);
	
	*line = ft_strsub(str,0,end);	
	if(str[end] == -1)
		str += end;
	else
		str += 1+end;
	
	return(1);
}
/*
int main()
{
    int fd = open("tst", O_RDONLY) ;
   int tst;

    char *line;

   line = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));

   for(int i= 0 ; i<16; i++)
   {
   tst = get_next_line(fd,&line);


  printf("%s\n\t%d\t%d\n",line,tst,i);
   }
  return(0);
}    
*/
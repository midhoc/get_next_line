/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 13:26:15 by midounhoc         #+#    #+#             */
/*   Updated: 2019/04/16 18:31:02 by hmidoun          ###   ########.fr       */
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
		 if(str[i] < 0)
		 	return(-2);
		i++;
	}
	return(-1);
}

char	*read_file(char *str, int fd)
{
	char	*tmp;
	int		ret;
	tmp =(char *)malloc(sizeof(char) * (BUFF_SIZE+1));
	if(!tmp)
		return(NULL);
	while ((ret = read(fd, tmp, BUFF_SIZE)) > 0)
		{
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

	if(fd == -1 || !(*line))
		return(-1);
	if(!str)
	{
		str = (char*)malloc(sizeof(char) * (BUFF_SIZE+1));
		if(!str)
			return(-1);
		str = read_file(str,fd);
	}
	end = search_end(str);

	*line = ft_strsub(str,0,end);
	if(end == -1)
	{
		//  str += (2+end);
		return(0);
	}
	str +=(1+end);
	return(1);
}
       /*

int main()
{
    int fd = open("tst", O_RDONLY) ;
   int tst;

    char *line;

   line = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));

   for(int i= 0 ; i<12; i++)
   {
   tst = get_next_line(fd,&line);



   //line = read_file(line,fd);

  printf("%s\n\t%d\t%d\n",line,tst,i);
   }
  return(0);
}         */

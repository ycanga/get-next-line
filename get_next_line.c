/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycanga <ycanga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:24:32 by egun              #+#    #+#             */
/*   Updated: 2022/08/25 00:44:32 by ycanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_error(int a, char *str, char *buffer)
{
	if (a < 0)
	{
		free (str);
		free (buffer);
		return (0);
	}
	return (1);
}

char	*getstr(int fd, char *str)
{
	int		a;
	char	*buffer;
	char	*s;

	if (!str)
		str = ft_strdup("");
	a = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while ((a != 0) && !(ft_strchr(str, '\n')))
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a == 0)
			break ;
		if (!check_error(a, str, buffer))
			return (NULL);
		buffer[a] = '\0';
		s = ft_strjoin(str, buffer);
		free(str);
		str = s;
	}
	free(buffer);
	return (str);
}

char	*getnewline(char *str)
{
	char	*ptr;
	int		len;

	if (!str)
		return (NULL);
	if (!*str)
		return (NULL);
	ptr = ft_strchr(str, '\n');
	if (!ptr)
		return (ft_strdup(str));
	ptr++;
	if (!*ptr)
		return (ft_strdup(str));
	len = ft_strlen(str) - ft_strlen(ptr);
	return (ft_substr(str, 0, len));
}

char	*getremain(char *str)
{
	char	*ptr;

	ptr = ft_strchr(str, '\n');
	if (!ptr)
	{
		free(str);
		return (NULL);
	}
	ptr++;
	if (!(*ptr))
	{
		free(str);
		return (NULL);
	}
	ptr = ft_strdup(ptr);
	free (str);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	str = getstr(fd, str);
	if (!str)
		return (NULL);
	line = getnewline(str);
	str = getremain(str);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int   main(int ac, char **av)
{
  int   fd;
  char *c;
  char	*map;
  int	i;
  int	j;
  char	**data;

  j = 0;  
  i = 0;
  map = av[1];

	if (ac == 2)
	{
		fd = open(map, O_RDWR);
		c = get_next_line(fd);
		// printf("%s", c);
		// c = get_next_line(c);
		// printf("%s", c);
		// while(c)
		// {
		// 	i++;
		// 	c = get_next_line(fd);
		// 	i = ft_strlen(c);
		// }
		data = &c;
		printf("%s", data[1]);
		while (c)
		{
			c = get_next_line(fd);
			i++;
		}
		printf("%s", c);
		data = &c;
		
		printf("%s", data[0]);
		
		
		//printf("%d", i);
		printf("%d", i);
		//system("leaks a.out");
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:20:44 by jtaravel          #+#    #+#             */
/*   Updated: 2021/12/23 18:01:55 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_read(char *buff, int fd)
{
	int		ret;
	char	*tmp;

	ret = 1;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (ret != 0 && !ft_strchr(buff, '\n'))
	{
		ret = read(fd, tmp, BUFFER_SIZE);
		if (ret == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[ret] = '\0';
		buff = ft_strjoin(buff, tmp);
	}
	free(tmp);
	return (buff);
}

char	*ft_next_line(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
	i++;
	j = 0;
	while (str[i + j])
	{
		tmp[j] = str[i + j];
		j++;
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		line = malloc(sizeof(char) * (i + 2));
	else
		line = malloc(sizeof(char) * (i + 1));
	while (str[j] && str[j] != '\n')
	{
		line[j] = str[j];
		j++;
	}
	if (str[j] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buff[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = ft_read(buff[fd], fd);
	if (!buff[fd])
		return (NULL);
	if (!buff[fd][0])
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(buff[fd]);
	buff[fd] = ft_next_line(buff[fd]);
	return (line);
}
/*
int main(void)
{
	char	*str;
	int	fd;
	int	fd1;
	fd = open("test.txt", O_RDONLY);
	fd1 = open("test2.txt", O_RDONLY);
	
	while((str = get_next_line(fd)) != NULL)
	{
		printf("%s",str);
		free(str);
	}
	while((str = get_next_line(fd1)) != NULL)
	{
		printf("%s",str);
		free(str);
	}
	return (0);
}
*/

int main(void)
{
        char    *str;
        int     fd;
        int     fd1;
        fd = open("get_next_line.c", O_RDONLY);
        fd1 = open("get_next_line.h", O_RDONLY);

        while((str = get_next_line(fd)) != NULL)
        {
                printf("%s",str);
                free(str);
                str = get_next_line(fd1);
                printf("%s",str);
                free(str);
        }
        return (0);
}

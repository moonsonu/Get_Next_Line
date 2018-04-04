/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 22:46:45 by ksonu             #+#    #+#             */
/*   Updated: 2018/04/04 00:39:51 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_line(const int fd, char **data, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (data[fd][i] != '\n' && data[fd][i] != '\0')
		i++;
	if (data[fd][i] == '\n')
	{
		*line = ft_strsub(data[fd], 0, i);
		tmp = ft_strdup(data[fd] + i + 1);
		ft_strdel(&data[fd]);
		data[fd] = tmp;
		if (data[fd][0] == '\0')
			ft_strdel(&data[fd]);
	}
	else if (data[fd][i] == '\0')
	{
		*line = ft_strdup(data[fd]);
		ft_strdel(&data[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static char		*data[1023];
	char			*tmp;
	int				f;

	if (fd < 0 || BUFF_SIZE < 1 || line == NULL)
		return (-1);
	while ((f = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[f] = '\0';
		if (data[fd] == NULL)
			data[fd] = ft_strnew(1);
		tmp = ft_strjoin(data[fd], buff);
		ft_strdel(&data[fd]);
		data[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (f < 0)
		return (-1);
	else if (f == 0 && data[fd] == NULL)
		return (0);
	return (gnl_line(fd, data, line));
}

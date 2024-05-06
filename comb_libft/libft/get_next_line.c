/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:07:40 by danevans          #+#    #+#             */
/*   Updated: 2024/05/04 09:08:26 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>

static char	*bytes_read(int fd, char *backup, char *buffer)
{
	char	*temp;
	ssize_t	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(backup, buffer);
		free(temp);
		if (ft_strchr(backup, '\n'))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes == -1)
	{
		free(buffer);
		free(backup);
		return (NULL);
	}
	free(buffer);
	return (backup);
}

static char	*ft_line(char *backup)
{
	int		count;
	char	*line;

	if (!backup)
		return (NULL);
	count = 0;
	while (backup[count] != '\0')
	{
		if (backup[count] == '\n')
			break ;
		count++;
	}
	line = malloc(sizeof(char) * (count + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup, count + 1);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*ft_update_backup(char *backup)
{
	int		count;
	char	*new_back;

	count = 0;
	while (backup[count] != '\0')
	{
		if (backup[count] == '\n')
			break ;
		count++;
	}
	if (backup[count] == '\0')
	{
		free (backup);
		return (NULL);
	}
	new_back = malloc(sizeof(char) * (ft_strlen(backup) - count + 1));
	if (!new_back)
		return (NULL);
	ft_strlcpy(new_back, backup + count + 1, ft_strlen(backup) - count + 1);
	free(backup);
	return (new_back);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free (buffer);
		return (NULL);
	}
	backup = bytes_read(fd, backup, buffer);
	if (backup == NULL)
		return (NULL);
	line = ft_line(backup);
	backup = ft_update_backup(backup);
	return (line);
}

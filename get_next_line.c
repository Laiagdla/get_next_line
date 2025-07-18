/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:54 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/18 18:14:00 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_memcpy(char *dest, char *src, size_t n, int rem)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return ;
	while (src[i] != '\0' && i < n && !(rem == 0 && src[i] == '\n'))
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	if (src[i] == '\n')
		dest[i++] = '\n';
	dest[i] = 0;
}

char	*ft_strchr(char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c || !c)
		return ((char *)s);
	return (NULL);
}

void	vars_alloc(char **str, char **reminder)
{
	int	i;

	*str = malloc(sizeof(char) * (BUFFER_SIZE +1));
	if (!*str)
		return ;
	i = BUFFER_SIZE;
	while (i--)
		(*str)[i] = 0;
	if (*reminder == NULL)
	{
		*reminder = malloc(sizeof(char) * (BUFFER_SIZE +1));
		if (!*reminder)
			return ;
		i = BUFFER_SIZE;
		while (i--)
			(*reminder)[i] = 0;
	}
}

t_line	*start(t_line *head, char *reminder, int size)
{
	char	*start;

	start = malloc(sizeof(char) * (BUFFER_SIZE +1));
	if (!start)
		return (NULL);
	if (*reminder != '\0')
	{
		ft_memcpy(start, reminder, BUFFER_SIZE, 1);
		link_chunk(&head, new_chunk(start));
		while (size--)
			reminder[size] = 0;
	}
	free(start);
	return (head);
}

char	*get_next_line(int fd)
{
	char			*str;
	static char		*reminder;
	t_line			*head;
	char			*line;

	vars_alloc(&str, &reminder);
	head = NULL;
	head = start(head, reminder, BUFFER_SIZE);
	while (read(fd, str, BUFFER_SIZE) > 0)
	{
		if (!ft_strchr(str, '\n'))
			link_chunk(&head, new_chunk(str));
		else
		{
			ft_memcpy(reminder, str, BUFFER_SIZE, 1);
			link_chunk(&head, new_chunk(str));
			while (*reminder != '\n' && *reminder != '\0')
				reminder++;
			reminder++;
			break ;
		}
	}
	line = chunks_to_str(head);
	return (line);
}

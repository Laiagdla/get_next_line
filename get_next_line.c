/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:54 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/21 16:37:53 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memcpy(char *dest, char *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (len-- && *s != '\n' && *s != '\0')
		*d++ = *s++;
	if (*s == '\n')
		*d++ = '\n';
	*d = 0;
	return (dest);
}

char	*find_nl(char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (s[i] == '\n')
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

void	link_chunk_shifted(t_line **head, char *chunk)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (chunk[i] != '\n' && chunk[i] != '\0')
		i++;
	if (chunk[i] == '\0')
	{
		chunk[j] = 0;
		return ;
	}
	i++;
	while (chunk[i] != '\0')
		chunk[j++] = chunk[i++];
	chunk[j] = 0;
	link_chunk(head, new_chunk(chunk));
}

char	*get_next_line(int fd)
{
	static char		chunk[BUFFER_SIZE +1];
	t_line			*head;
	char			*line;
	int				b_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = NULL;
	if (chunk[0] != 0)
		link_chunk_shifted(&head, chunk);
	b_read = read(fd, chunk, BUFFER_SIZE);
	while (b_read > 0)
	{
		chunk[b_read] = '\0';
		if (!find_nl(chunk, b_read) && link_chunk(&head, new_chunk(chunk)))
			b_read = read(fd, chunk, BUFFER_SIZE);
		else if (link_chunk(&head, new_chunk(chunk)))
			break ;
	}
	line = chunks_to_str(head);
	// if (!find_nl(chunk, b_read))
	// 	chunk[0] = 0;
	return (line);
}

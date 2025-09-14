/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:54 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/08/29 14:28:32 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_nl(const char *buffer, size_t buffer_size)
{
	int	i;

	i = 0;
	while (i < (int)buffer_size && buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

size_t	find_line_end(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (line[i] == '\n')
			return (i + 1);
		if (line[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

static void	shift_chunk(char *chunk, size_t start_index)
{
	size_t	i;

	i = 0;
	while (chunk[start_index + i] != '\0')
	{
		chunk[i] = chunk[start_index + i];
		i++;
	}
	while (i < BUFFER_SIZE + 1)
	{
		chunk[i] = '\0';
		i++;
	}
}

static char	*chunks_to_line(t_line *head)
{
	size_t	count;
	char	*line_ptr;
	char	*line;
	t_line	*temp_head;
	int		i;

	if (!head)
		return (NULL);
	count = count_chunks(head);
	line = malloc(sizeof(char) * (BUFFER_SIZE * count +1));
	line_ptr = line;
	temp_head = head;
	while (temp_head)
	{
		i = 0;
		while (temp_head->chunk[i])
		{
			*line = temp_head->chunk[i++];
			line++;
		}
		temp_head = temp_head->next;
	}
	line_ptr[find_line_end(line_ptr)] = '\0';
	clear_line(&head);
	return (line_ptr);
}

char	*get_next_line(int fd)
{
	static char	chunk[BUFFER_SIZE + 1];
	t_line		*head;
	char		*line;
	int			nl_index;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = NULL;
	nl_index = find_nl(chunk, BUFFER_SIZE);
	if (chunk[0] != '\0')
	{
		link_chunk(&head, new_chunk(chunk));
		shift_chunk(chunk, nl_index + 1);
	}
	while (nl_index == -1)
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		chunk[bytes_read] = '\0';
		link_chunk(&head, new_chunk(chunk));
		nl_index = find_nl(chunk, BUFFER_SIZE);
		if (nl_index != -1)
		{
			shift_chunk(chunk, nl_index + 1);
			break ;
		}
	}
	if (bytes_read < 0 || (bytes_read == 0 && !head))
	{
		clear_line(&head);
		return (NULL);
	}
	line = chunks_to_line(head);
	return (line);
}

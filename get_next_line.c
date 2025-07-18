/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:54 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/18 13:19:47 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(sizeof(char) * size +1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0' && i < size)
	{
		ptr[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		ptr[i] = '\n';
	ptr[++i] = 0;
	return (ptr);
}

char	*ft_strchr(char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c || !c)
		return ((char *)s);
	return (NULL);
}

void	*line_str_alloc(t_line **head, char **str, char **reminder)
{
	int	i;

	*head = malloc(sizeof(t_line));
	*str = malloc(sizeof(char) * (BUFFER_SIZE +1));
	if (!*head || !*str)
		return (NULL);
	i = BUFFER_SIZE;
	while (i--)
		(*str)[i] = 0;
	if (*reminder == NULL)
	{
		*reminder = malloc(sizeof(char) * (BUFFER_SIZE +1));
		if (!*reminder)
			return (NULL);
		i = BUFFER_SIZE;
		while (i--)
			(*reminder)[i] = 0;
	}
	return (*head);
}

char	*get_next_line(int fd)
{
	char			*str;
	static char		*reminder;
	t_line			*head;
	int				i;

	if (line_str_alloc(&head, &str, &reminder) == NULL)
		return (NULL);
	if (*reminder != '\0')
	{
		if (*reminder == '\n')
			reminder++;
		link_chunk(&head, new_chunk(reminder));
		i = BUFFER_SIZE;
		while (i--)
			reminder[i] = 0;
	}
	while (*reminder == '\0')
	{
		if (read(fd, str, BUFFER_SIZE) > 0)
		{
			if (!ft_strchr(str, '\n'))
				link_chunk(&head, new_chunk(str));
			if (ft_strchr(str, '\n'))
			{
				reminder = str;
				link_chunk(&head, new_chunk(str));
				while (*reminder != '\n' && *reminder != '\0')
					reminder++;
			}
		}
		else
			return (NULL);
	}
	str = chunks_to_str(head, str);
	return (str);
}

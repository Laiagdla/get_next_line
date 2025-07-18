/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:54 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/17 17:40:24 by lgrobe-d         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	char			*str;
	static char		*reminder;
	t_line			*head;

	head = malloc(sizeof(t_line));
	if (reminder++ != NULL)
		ft_lstadd_chunk(&head, ft_lstnew(reminder));
	str = malloc(sizeof(char) * (BUFFER_SIZE +1));
	reminder = malloc(sizeof(char) * (BUFFER_SIZE +1));
	reminder[0] = '\0';
	while (reminder[0] == '\0')
	{
		if (read(fd, str, BUFFER_SIZE))
		{
			str[BUFFER_SIZE +1] = '\0';
			if (!ft_strchr(str, '\n'))
				ft_lstadd_chunk(&head, ft_lstnew(str));
			if (ft_strchr(str, '\n'))
			{
				reminder = str;
				ft_lstadd_chunk(&head, ft_lstnew(str));
				while (*reminder != '\n' && *reminder != '\0')
					reminder++;
			}
		}
		else
			return (NULL);
	}
	// ft_lstprint(head);
	str = ft_line(head, str);
	return (str);
}

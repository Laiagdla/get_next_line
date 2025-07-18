/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:32:02 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/17 17:40:02 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c || !c)
		return ((char *)s);
	return (NULL);
}

t_line	*ft_lstnew(char *content)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content, BUFFER_SIZE);
	new->next = NULL;
	return (new);
}

t_line	*ft_lstlast(t_line *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void	ft_lstadd_chunk(t_line **head, t_line *new)
{
	t_line	*temp;

	if (!*head)
		*head = new;
	else
	{
		temp = ft_lstlast(*head);
		temp->next = new;
	}
}

void	ft_lstprint(t_line *head)
{
	while (head)
	{
		write(1, head->content, 5);
		head = head->next;
	}

}

size_t	ft_lstsize(t_line *head)
{
	size_t	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	*ft_line(t_line *head, char *str)
{
	size_t	count;
	char	*content;
	char	*ptr;

	count = ft_lstsize(head);
	str = malloc(sizeof(char) * (BUFFER_SIZE +1) * count);
	ptr = str;
	while (head)
	{
		content = head->content;
		while (content && *content)
			*str++ = *content++ ;
		head = head->next;
	}
	*str = '\0';
	return (ptr);
}

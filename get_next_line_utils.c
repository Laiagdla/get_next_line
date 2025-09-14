/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:32:02 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/08/29 14:27:21 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	*new_chunk(char *chunk)
{
	t_line	*new;

	if (chunk == NULL || *chunk == '\0')
		return (NULL);
	new = malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->chunk = ft_strldup(chunk);
	if (!new->chunk)
		return (NULL);
	new->next = NULL;
	return (new);
}

int	link_chunk(t_line **head, t_line *new)
{
	t_line	*temp;

	if (!new)
		return (0);
	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (1);
}

size_t	count_chunks(t_line *head)
{
	size_t	count;

	count = 0;
	while (head && ++count)
		head = head->next;
	return (count);
}

void	clear_line(t_line **head)
{
	t_line	*current;
	t_line	*next;

	if (!*head)
		return ;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->chunk != NULL)
			free(current->chunk);
		free(current);
		current = next;
	}
	*head = NULL;
}

char	*ft_strldup(char *src)
{
	char	*dst;
	char	*start;
	size_t	len;

	if (!src)
		return (NULL);
	len = find_line_end(src);
	dst = (char *)malloc(sizeof(char) * len);
	if (!dst)
		return (NULL);
	start = dst;
	while (*src && len--)
		*dst++ = *src++;
	*dst = '\0';
	return (start);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:32:02 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/18 13:10:09 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	*ft_lstnew(char *str)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str, BUFFER_SIZE);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_chunk(t_line **head, t_line *new)
{
	t_line	*temp;

	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
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
	char	*temp_str;
	char	*start_str;

	count = ft_lstsize(head);
	str = malloc(sizeof(char) * (BUFFER_SIZE +1) * count);
	if (!str)
		return (NULL);
	start_str = str;
	while (head)
	{
		temp_str = head->str;
		while (temp_str && *temp_str)
			*str++ = *temp_str++ ;
		head = head->next;
	}
	*str = '\0';
	return (start_str);
}

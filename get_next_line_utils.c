/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:32:02 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/18 18:06:03 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	*new_chunk(char *str)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->str = (char *)malloc(sizeof(char) * BUFFER_SIZE +1);
	if (!new->str && str)
	{
		free(new);
		return (NULL);
	}
	ft_memcpy(new->str, str, BUFFER_SIZE, 0);
	new->next = NULL;
	return (new);
}

void	link_chunk(t_line **head, t_line *new)
{
	t_line	*temp;

	if (!new)
		return ;
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

size_t	count_chunks(t_line *head)
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

void	clear_line(t_line **head)
{
	t_line	*current;
	t_line	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->str != NULL)
			free(current->str);
		free(current);
		current = next;
	}
	*head = NULL;
}

char	*chunks_to_str(t_line *head)
{
	size_t	count;
	char	*start_str;
	char	*line;
	t_line	*temp_head;
	int		i;

	count = count_chunks(head);
	line = malloc(sizeof(char) * (BUFFER_SIZE * count +1));
	start_str = line;
	temp_head = head;
	while (temp_head)
	{
		i = 0;
		while (temp_head->str[i])
		{
			*line = temp_head->str[i];
			line++;
			i++;
		}
		temp_head = temp_head->next;
	}
	*line = '\0';
	clear_line(&head);
	return (start_str);
}

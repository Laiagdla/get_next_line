/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_debug.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:51:24 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/08/29 13:00:56 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstprint(t_line *head)
{
	while (head)
	{
		write(1, head->chunk, BUFFER_SIZE);
		head = head->next;
	}
}

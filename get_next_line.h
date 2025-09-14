/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:30:43 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/08/29 14:27:33 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_line
{
	char			*chunk;
	struct s_line	*next;
}	t_line;

size_t	find_line_end(char *line);
char	*get_next_line(int fd);

t_line	*new_chunk(char *chunk);
int		link_chunk(t_line **head, t_line *new);
size_t	count_chunks(t_line *head);
void	clear_line(t_line **head);
char	*ft_strldup(char *src);

#endif

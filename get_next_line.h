/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:30:43 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/18 18:01:53 by lgrobe-d         ###   ########.fr       */
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
	char			*str;
	struct s_line	*next;
}	t_line;

void	ft_memcpy(char *dest, char *src, size_t n, int rem);
char	*ft_strchr(char *s, int c);
void	vars_alloc(char **str, char **reminder);
t_line	*start(t_line *head, char *reminder, int size);
char	*get_next_line(int fd);

t_line	*new_chunk(char *str);
void	link_chunk(t_line **head, t_line *new);
size_t	count_chunks(t_line *head);
void	clear_line(t_line **head);
char	*chunks_to_str(t_line *head);

#endif

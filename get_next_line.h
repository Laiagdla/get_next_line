/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:30:43 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/17 17:53:54 by lgrobe-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_line
{
	void			*content;
	struct s_line	*next;
}	t_line;

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
t_line	*ft_lstnew(char *content);
t_line	*ft_lstlast(t_line *head);
void	ft_lstadd_chunk(t_line **head, t_line *new);
void	ft_lstprint(t_line *head);
char	*ft_strdup(char *s, size_t size);
char	*ft_line(t_line *head, char *str);

#endif

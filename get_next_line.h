/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrobe-d <lgrobe-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:30:43 by lgrobe-d          #+#    #+#             */
/*   Updated: 2025/07/18 13:19:47 by lgrobe-d         ###   ########.fr       */
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
	void			*str;
	struct s_line	*next;
}	t_line;

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s, size_t size);
t_line	*new_chunk(char *str);
void	link_chunk(t_line **head, t_line *new);
size_t	count_chunks(t_line *head);
char	*chunks_to_str(t_line *head, char *str);
void	ft_lstprint(t_line *head);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:21:48 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/23 16:55:48 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnlist
{
	int				fd;
	char			leave[BUFFER_SIZE + 1];
	struct s_gnlist	*next;
}	t_gnlist;

char		*get_next_line(int fd);
t_gnlist	*gnl_lstadd_back(t_gnlist **head, int fd);
char		*gnl_setstr(char	*leave, t_gnlist *cur);
char		*read_n_join(char *toss, int fd, int size);
char		*gnl_newstr(char *toss, int *size);
int			gnl_strcat(char *toss, char *buf);
char		*gnl_substr(char *toss, t_gnlist *cur, int len);
int			gnl_check(char *toss);
void		gnl_lstdel(t_gnlist **head, int fd);

#endif

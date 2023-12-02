/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:13:56 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/23 16:55:54 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnlist	*head;
	char			*toss;
	t_gnlist		*cur;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	cur = gnl_lstadd_back(&head, fd);
	if (cur == 0)
		return (0);
	toss = gnl_setstr(cur->leave, cur);
	if (cur->leave[0] == 0 && gnl_check(toss))
	{
		toss = read_n_join(toss, fd, BUFFER_SIZE);
		toss = gnl_substr(toss, cur, 0);
	}
	if (toss == 0)
		gnl_lstdel(&head, fd);
	return (toss);
}

t_gnlist	*gnl_lstadd_back(t_gnlist **head, int fd)
{
	t_gnlist	*cur;
	t_gnlist	*tmp;

	cur = *head;
	while (cur != NULL)
	{
		tmp = cur;
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	cur = (t_gnlist *)malloc(sizeof(t_gnlist));
	if (cur == 0)
		return (0);
	cur->fd = fd;
	cur->next = NULL;
	cur->leave[0] = 0;
	if (*head == 0)
		*head = cur;
	else
		tmp->next = cur;
	return (cur);
}

char	*gnl_setstr(char *leave, t_gnlist *cur)
{
	char	*toss;
	int		i;

	i = 0;
	while (cur->leave[i] != 0 && cur->leave[i] != '\n')
		i++;
	if (cur->leave[i] == '\n')
		i++;
	toss = (char *)malloc(i + 1);
	if (toss == 0)
		return (0);
	i = 0;
	while (*leave != 0 && *leave != '\n')
		toss[i++] = *leave++;
	if (*leave == '\n')
		toss[i++] = *leave++;
	toss[i] = 0;
	i = 0;
	while (*leave != 0)
		cur->leave[i++] = *leave++;
	cur->leave[i] = 0;
	return (toss);
}

char	*read_n_join(char *toss, int fd, int size)
{
	char	buf[BUFFER_SIZE + 1];
	int		readsize;
	int		count;

	count = 0;
	while (++count)
	{
		readsize = read(fd, buf, BUFFER_SIZE);
		if (readsize <= 0)
		{
			if (toss[0] == 0 || readsize < 0)
			{
				free(toss);
				toss = 0;
			}
			return (toss);
		}
		buf[readsize] = 0;
		if (size <= BUFFER_SIZE * count)
			toss = gnl_newstr(toss, &size);
		if (gnl_strcat(toss, buf) == 1)
			return (toss);
	}
	return (0);
}

char	*gnl_substr(char *toss, t_gnlist *cur, int len)
{
	char	*compact;
	int		i;

	if (toss == 0)
		return (0);
	while (toss[len] != 0 && toss[len] != '\n')
		len++;
	if (toss[len] == '\n')
		len++;
	compact = (char *)malloc(len + 1);
	if (compact == 0)
	{
		free(toss);
		return (0);
	}
	i = -1;
	while (++i < len)
		compact[i] = toss[i];
	compact[i] = 0;
	i = 0;
	while (toss[len] != 0)
		cur->leave[i++] = toss[len++];
	cur->leave[i] = 0;
	free(toss);
	return (compact);
}

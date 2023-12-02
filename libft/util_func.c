/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:08:40 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/23 16:36:01 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_init(char c, char *s)
{
	int	count;

	count = 0;
	while (s[count])
	{
		if (s[count] == c)
			return (count);
		count++;
	}
	return (-1);
}

char	*ftp_calloc(int count)
{
	char	*tmp;
	int		i;

	tmp = (char *)malloc(count);
	if (tmp == 0)
		return (0);
	i = 0;
	while (i < count)
		tmp[i++] = 0;
	return (tmp);
}

int	ftp_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	ftp_strncpy(char *dest, char *src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dest[i] = src[i];
		i++;
	}
}

void	fill_blank(char *tmp, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->field)
	{
		if (tmp[i] == 0)
			tmp[i] = ' ';
		i++;
	}
}

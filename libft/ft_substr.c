/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:07:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/08 12:37:58 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_checklen(char const *s, unsigned int start, size_t len)
{
	unsigned int	index;

	index = 0;
	while ((size_t)index < len && s[start + index] != 0)
		index++;
	return ((size_t)index);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*toss;
	size_t	num;
	size_t	index;

	if (s == 0)
		return (0);
	if (start >= ft_strlen(s))
	{
		toss = ft_calloc(1, 1);
		return (toss);
	}
	num = ft_checklen(s, start, len);
	toss = (char *)ft_calloc(num + 1, sizeof(char));
	if (toss == 0)
		return (0);
	index = 0;
	while (index < num)
	{
		toss[index] = s[start + index];
		index++;
	}
	return (toss);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:36:20 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/09 21:22:58 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(char *check, char **ptr, size_t count)
{
	size_t	index;

	if (check != 0)
		return (1);
	index = 0;
	while (index < count)
		free(ptr[index++]);
	free(ptr);
	return (0);
}

static size_t	ft_countword(char const *s, char c)
{
	size_t	flag;
	size_t	count;

	count = 0;
	flag = 1;
	while (*s)
	{
		if (*s != c && flag == 1)
		{
			count++;
			flag = 0;
		}
		else if (*s == c)
			flag = 1;
		s++;
	}
	return (count);
}

static size_t	ft_inlen(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (*s == c)
		s++;
	while (s[size] != c && s[size] != 0)
		size++;
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**toss;
	size_t	count;
	size_t	index;
	size_t	wordlen;

	if (s == 0)
		return (0);
	wordlen = ft_countword(s, c);
	toss = (char **)ft_calloc(wordlen + 1, sizeof(char *));
	if (toss == 0)
		return (0);
	count = 0;
	while (count < wordlen)
	{
		index = 0;
		toss[count] = (char *)ft_calloc(ft_inlen(s, c) + 1, sizeof(char));
		if (ft_free(toss[count], toss, count) == 0)
			return (0);
		while (*s == c && *s != 0)
			s++;
		while (*s != c && *s != 0)
			toss[count][index++] = *s++;
		count++;
	}
	return (toss);
}

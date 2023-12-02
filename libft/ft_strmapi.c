/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:56:23 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/08 17:13:54 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*toss;
	size_t	slen;
	size_t	index;

	if (s == 0)
		return (0);
	slen = ft_strlen(s);
	toss = (char *)ft_calloc(slen + 1, sizeof(char));
	if (toss == 0)
		return (0);
	index = 0;
	while (index < slen)
	{
		toss[index] = f(index, s[index]);
		index++;
	}
	return (toss);
}

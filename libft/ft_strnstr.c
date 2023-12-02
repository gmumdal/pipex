/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:21:53 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/06 15:55:44 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	if (haystack == 0 && len == 0)
		return (0);
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i1] != 0 && i1 < len)
	{
		i2 = 0;
		if (haystack[i1] == needle[i2])
		{
			while (haystack[i1 + i2] == needle[i2] && needle[i2] != 0)
			{
				if (i1 + i2 == len)
					return (0);
				i2++;
			}
			if (needle[i2] == 0)
				return ((char *)&haystack[i1]);
		}
		i1++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:53:13 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/11 12:46:13 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		count;
	char		*str_dst;
	const char	*str_src;

	if (dst == 0 && src == 0)
		return (dst);
	str_dst = dst;
	str_src = src;
	count = 0;
	while (count < n)
	{
		str_dst[count] = str_src[count];
		count++;
	}
	return (dst);
}

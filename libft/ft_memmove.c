/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:18:01 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/11 12:47:14 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*str_dst;
	const char	*str_src;

	if (dst == 0 && src == 0)
		return (dst);
	str_dst = dst;
	str_src = src;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len-- != 0)
			str_dst[len] = str_src[len];
	}
	return (dst);
}

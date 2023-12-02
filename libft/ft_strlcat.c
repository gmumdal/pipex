/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:53:07 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/11 14:23:43 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	if (dst == 0 && dstsize == 0)
		return (dstsize + ft_strlen(src));
	dstlen = 0;
	while (dstlen + 1 < dstsize && dst[dstlen] != 0)
		dstlen++;
	if (dst[dstlen] != 0 || dstsize == 0)
		return (dstsize + ft_strlen(src));
	srclen = 0;
	while (dstlen + srclen + 1 < dstsize && src[srclen] != 0)
	{
		dst[dstlen + srclen] = src[srclen];
		srclen++;
	}
	dst[dstlen + srclen] = 0;
	return (dstlen + ft_strlen(src));
}

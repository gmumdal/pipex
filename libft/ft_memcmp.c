/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:29:03 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/05 22:47:07 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				count;
	const unsigned char	*str_s1;
	const unsigned char	*str_s2;

	count = 0;
	str_s1 = s1;
	str_s2 = s2;
	while (count < n)
	{
		if (str_s1[count] != str_s2[count])
			return (str_s1[count] - str_s2[count]);
		count++;
	}
	return (0);
}

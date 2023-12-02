/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:50:32 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/11 13:24:48 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	count;

	count = 0;
	while (s[count] != 0)
		count++;
	if ((char)c == 0)
		return ((char *)&s[count]);
	while (count-- > 0)
	{
		if (s[count] == (char)c)
			return ((char *)&s[count]);
	}
	return (0);
}

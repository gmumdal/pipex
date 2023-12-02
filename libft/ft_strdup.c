/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:13 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/11 12:09:40 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*toss;
	int		len;

	len = ft_strlen(s1);
	toss = (char *)malloc(sizeof(char) * (len + 1));
	if (toss == 0)
		return (0);
	toss[len] = 0;
	while (len-- > 0)
		toss[len] = s1[len];
	return (toss);
}

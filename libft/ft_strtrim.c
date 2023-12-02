/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:43:31 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/10 11:14:08 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*toss;
	int		index;
	int		start;
	int		end;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	while (ft_strchr(set, s1[start]) != 0 && s1[start] != 0)
		start++;
	end = ft_strlen(s1) - 1;
	if (end < 0)
		return (ft_calloc(1, 1));
	while (end > -1 && ft_strchr(set, s1[end]) != 0 && s1[end] != 0)
		end--;
	if (start > end)
		return (ft_calloc(1, 1));
	toss = (char *)ft_calloc(end - start + 2, sizeof(char));
	if (toss == 0)
		return (0);
	index = 0;
	while (start <= end)
		toss[index++] = s1[start++];
	return (toss);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:28:53 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/11 13:31:28 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*toss;
	size_t	max;

	max = -1;
	if (count * size == 0)
		return (malloc(0));
	if (size >= max / count)
		return (0);
	toss = malloc(count * size);
	if (toss == 0)
		return (0);
	ft_bzero(toss, count * size);
	return (toss);
}

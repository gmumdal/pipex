/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:56:10 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/11 13:13:05 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	toss;
	int	plma;

	toss = 0;
	plma = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		plma = -1;
	}
	while (*str >= '0' && *str <= '9' && *str != 0)
	{
		toss = 10 * toss + (*str - '0');
		str++;
	}
	return (toss * plma);
}

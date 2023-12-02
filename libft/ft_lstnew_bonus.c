/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:28:00 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/10/09 19:35:56 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*toss;

	toss = (t_list *)malloc(sizeof(t_list) * 1);
	if (toss == 0)
		return (0);
	toss->next = NULL;
	toss->content = content;
	return (toss);
}

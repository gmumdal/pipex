/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:17:14 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/05 17:30:01 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	lst;
	t_buf	*buf;
	int		total;

	va_start(lst, s);
	buf = buf_setting();
	if (buf == 0)
		return (-1);
	if (buf_input(buf, (char *)s, lst) == 0)
	{
		free(buf->buffer);
		free(buf);
		return (-1);
	}
	total = write(1, buf->buffer, buf->index);
	free(buf->buffer);
	free(buf);
	va_end(lst);
	return (total);
}

char	*make_tmp(t_info *info, va_list lst)
{
	char	*tmp;

	if (info->type == 'c')
		tmp = make_char(info, va_arg(lst, int));
	else if (info->type == 's')
		tmp = make_str(info, va_arg(lst, char *), "(null)");
	else if (info->type == 'i' || info->type == 'd')
		tmp = make_nbr(info, va_arg(lst, int), 0, 0);
	else if (info->type == 'x')
		tmp = make_hexa(info, va_arg(lst, unsigned int), "0123456789abcdefx");
	else if (info->type == 'X')
		tmp = make_hexa(info, va_arg(lst, unsigned int), "0123456789ABCDEFX");
	else if (info->type == 'p')
		tmp = make_hexa(info, va_arg(lst, unsigned long), "0123456789abcdefx");
	else if (info->type == 'u')
		tmp = make_unsign(info, va_arg(lst, unsigned int));
	else
		tmp = make_normal(info, info->type);
	if (tmp == 0)
		return (0);
	return (tmp);
}

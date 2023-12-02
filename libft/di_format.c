/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:23:07 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/23 16:41:15 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*make_nbr(t_info *info, int nbr, char front, int len)
{
	char	*tmp;
	char	*num;

	front_n_len(nbr, &len, &front, info);
	num = ftp_itoa(front, len, nbr, info);
	if (num == 0)
		return (0);
	if (info->field < ftp_strlen(num))
		info->field = ftp_strlen(num);
	tmp = ftp_calloc(info->field + 1);
	if (tmp == 0)
	{
		free(num);
		return (0);
	}
	if (info->left == 1)
		ftp_strncpy(tmp, num, ftp_strlen(num));
	else if (info->left == 0)
		ftp_strncpy(&tmp[info->field - ftp_strlen(num)], num, ftp_strlen(num));
	fill_blank(tmp, info);
	free(num);
	return (tmp);
}

void	front_n_len(int nbr, int *len, char *front, t_info *info)
{
	int	flag;

	if (info->blank == 1)
		*front = ' ';
	if (nbr < 0)
		*front = '-';
	else if (info->plma == 1)
		*front = '+';
	if (nbr == 0)
		*len = 1;
	while (nbr != 0)
	{
		(*len)++;
		nbr /= 10;
	}
	flag = 0;
	if (*front != 0)
		flag = 1;
	if (info->pre > *len)
		*len = info->pre;
	if (info->pre == -1 && info->zero == 1
		&& info->left == 0 && *len < info->field - flag)
		*len = info->field - flag;
}

char	*ftp_itoa(char front, int len, long long ln, t_info *info)
{
	char	*num;
	int		flag;
	int		i;

	if (info->pre == 0 && ln == 0)
		len = 0;
	flag = 0;
	if (ln < 0)
		ln = -ln;
	if (front != 0)
		flag = 1;
	num = ftp_calloc(len + flag + 1);
	if (num == 0)
		return (0);
	if (front != 0)
		num[0] = front;
	i = -1;
	while (++i < len)
	{
		num[i + flag] = ln % 10 + '0';
		ln = ln / 10;
	}
	ftp_swap(num, len, flag);
	return (num);
}

void	ftp_swap(char *num, int len, int flag)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < len / 2)
	{
		tmp = num[i + flag];
		num[i + flag] = num[len + flag - i - 1];
		num[len + flag - i - 1] = tmp;
		i++;
	}
}

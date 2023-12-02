/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:53:37 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/23 16:38:31 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_buf
{
	char	*buffer;
	int		index;
	int		size;
}	t_buf;

typedef struct s_info
{
	int	field;
	int	shop;
	int	left;
	int	pre;
	int	type;
	int	plma;
	int	blank;
	int	zero;
}	t_info;

int		ft_printf(const char *s, ...);
int		buf_input(t_buf *buf, char *s, va_list lst);
t_info	*check_option(char **s);
int		buf_join(t_buf *buf, t_info *info, va_list lst);
char	*make_tmp(t_info *info, va_list lst);
t_info	*info_init(void);
void	info_option(char *s, t_info *info);
void	info_field(char **s, t_info *info);
void	info_pre(char **s, t_info *info);
int		is_init(char c, char *s);
t_buf	*buf_setting(void);
char	*ftp_calloc(int count);
int		ftp_strlen(char *s);
int		buf_char(t_buf *buf, char c);
char	*make_char(t_info *info, char c);
char	*make_normal(t_info *info, char c);
char	*make_str(t_info *info, char *s1, char *s);
void	ftp_strncpy(char *dest, char *src, int count);
char	*make_nbr(t_info *info, int nbr, char front, int len);
void	front_n_len(int nbr, int *len, char *front, t_info *info);
char	*ftp_itoa(char front, int len, long long nbr, t_info *info);
void	fill_blank(char *tmp, t_info *info);
void	ftp_swap(char *num, int len, int flag);
char	*make_hexa(t_info *info, unsigned long nbr, char *hexa_base);
void	hexa_len_flag(unsigned long nbr, t_info *info, int *len, int *flag);
char	*ftp_itoa_hexa(unsigned long nbr, char *hexa_base, t_info *info);
char	*make_unsign(t_info *info, unsigned int nbr);
int		unsign_len_check(unsigned int nbr, t_info *info);
char	*ftp_itoa_unsign(unsigned int nbr, t_info *info);

#endif

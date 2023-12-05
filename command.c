/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:02:17 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/05 15:24:51 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**make_command(char *cmd)
{
	char	**tmp;

	if (ft_strchr(cmd, '\'') == 0 && ft_strchr(cmd, '\"') == 0)
		tmp = cmd_split(cmd, 0);
	else if (ft_strchr(cmd, '\'') != 0 && ft_strchr(cmd, '\"') != 0)
	{
		if (ft_strchr(cmd, '\'') < ft_strchr(cmd, '\"'))
			tmp = cmd_split(cmd, '\'');
		else
			tmp = cmd_split(cmd, '\"');
	}
	else if (ft_strchr(cmd, '\'') != 0)
		tmp = cmd_split(cmd, '\'');
	else
		tmp = cmd_split(cmd, '\"');
	return (tmp);
}

char	**cmd_split(char *cmd, char sep)
{
	char	**toss;
	int		count;
	int		index;
	int		wordlen;

	wordlen = cmd_countword(cmd, sep);
	toss = (char **)ft_calloc(wordlen + 1, sizeof(char *));
	if (toss == 0)
		error_print(errno);
	count = 0;
	while (count < wordlen)
	{
		index = 0;
		toss[count] = (char *)ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
		if (toss[count] == 0)
			error_print(errno);
		cmd_input(toss[count], &cmd, sep);
		count++;
	}
	return (toss);
}

int	cmd_countword(char *cmd, char sep)
{
	int	flag;
	int	count;

	count = 0;
	flag = 1;
	while (*cmd)
	{
		if (*cmd == '\\')
			cmd++;
		else if (*cmd == sep && flag != 2 && count++ > -1)
			flag = 2;
		else if (*cmd == sep && flag == 2)
			flag = 1;
		else if (*cmd != ' ' && flag == 1 && count++ > -1)
			flag = 0;
		else if (*cmd == ' ' && flag != 2)
			flag = 1;
		cmd++;
	}
	return (count);
}

void	cmd_input(char *toss, char **cmd, char sep)
{
	int	i;

	i = 0;
	if (**cmd == sep)
	{
		(*cmd)++;
		while (**cmd != sep)
		{
			if (**cmd == '\\')
				(*cmd)++;
			toss[i++] = *(*cmd)++;
		}
		(*cmd)++;
	}
	else
	{
		while (**cmd != ' ' && **cmd != 0)
		{
			if (**cmd == '\\')
				(*cmd)++;
			toss[i++] = *(*cmd)++;
		}
	}
	while (**cmd == ' ')
		(*cmd)++;
}

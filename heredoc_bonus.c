/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:47:48 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/02 18:34:51 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	make_heredoc(int *fd, char **av, char *heredoc)
{
	char	*tmp;
	char	*endstr;

	endstr = ft_strjoin(av[2], "\n", "");
	while (42)
	{
		tmp = get_next_line(0);
		if (tmp == 0)
			exit(0);
		if (ft_strncmp(tmp, endstr, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			free(endstr);
			break ;
		}
		ft_putstr_fd(tmp, fd[0]);
		free(tmp);
	}
	close(fd[0]);
	fd[0] = open(heredoc, O_RDONLY);
}

void	heredoc_setting(int ac, char **av, t_data *data, char **env)
{
	int	i;

	data->pipe = (int **)malloc(sizeof(int *) * (ac - 5));
	data->id = (pid_t *)malloc(sizeof(pid_t) * (ac - 4));
	if (data->pipe == 0 || data->id == 0)
		error_print(2);
	i = 0;
	while (i < ac - 4)
	{
		data->pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (data->pipe[i] == 0)
			error_print(2);
		i++;
	}
	data->path = path_setting(env);
	data->cmd_num = ac - 4;
	data->cmd = av + 3;
}

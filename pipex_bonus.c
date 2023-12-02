/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:10:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/02 18:36:11 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_print(int flag)
{
	if (flag == 1)
		write(2, "Error\n", 6);
	else if (flag == 2)
		write(2, "Malloc Error\n", 13);
	exit(-1);
}

void	close_fd(t_data *data, int *fd)
{
	int	i;

	i = 0;
	while (i < data->cmd_num - 1)
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
}

void	ending_free(t_data *data)
{
	int	i;

	i = 0;
	while (data->path[i] != 0)
		free(data->path[i++]);
	free(data->path);
	i = 0;
	while (i < data->cmd_num - 1)
		free(data->pipe[i++]);
	free(data->pipe);
	free(data->id);
}

void	ending(t_data *data, int *fd, char *heredoc)
{
	int		status;

	close_fd(data, fd);
	while (42)
	{
		if (wait(&status) == -1)
			break ;
	}
	ending_free(data);
	unlink(heredoc);
	free(heredoc);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		i;
	t_data	data;
	char	*heredoc;

	if (ac == 1)
		error_print(1);
	if (open_check(ac, av, fd, &heredoc) == 1)
	{
		heredoc_setting(ac, av, &data, env);
		make_heredoc(fd, av, heredoc);
	}
	else
		first_setting(ac, av, &data, env);
	i = 0;
	while (i < data.cmd_num)
		make_child(&data, fd, i++, env);
	ending(&data, fd, heredoc);
	return (0);
}

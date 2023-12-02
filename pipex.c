/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:10:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/02 18:35:15 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		i;
	int		status;
	t_data	data;

	if (ac != 5)
		error_print(1);
	open_check(ac, av, fd);
	first_setting(ac, av, &data, env);
	i = 0;
	while (i < data.cmd_num)
		make_child(&data, fd, i++, env);
	close_fd(&data, fd);
	while (1)
	{
		if (wait(&status) == -1)
			break ;
	}
	ending_free(&data);
}

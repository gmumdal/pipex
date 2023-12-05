/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:24:18 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/05 15:22:50 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_child(t_data *data, char **av, int i, char **env)
{
	if (i < data->cmd_num - 1)
	{
		if (pipe(data->pipe) == -1)
			error_print(errno);
		data->id[i] = fork();
		if (data->id[i] == 0)
		{
			if (i == 0)
				command_exec_first(data, av, env);
		}
	}
	else if (i == data->cmd_num - 1)
	{
		data->id[i] = fork();
		if (data->id[i] == 0)
			command_exec_end(data, av, env);
	}
}

void	command_exec_first(t_data *data, char **av, char **env)
{
	int		fd;
	char	**command;
	char	*path;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_print(errno);
	close(data->pipe[0]);
	command = make_command(data->cmd[0]);
	if (command == 0)
		error_print(errno);
	path = path_search(data->path, command[0]);
	if (dup2(fd, 0) == -1)
		error_print(errno);
	close(fd);
	if (dup2(data->pipe[1], 1) == -1)
		error_print(errno);
	close(data->pipe[1]);
	if (execve(path, command, env) == -1)
		error_print(126);
}

void	command_exec_end(t_data *data, char **av, char **env)
{
	char	**command;
	char	*path;
	int		fd;

	fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		error_print(errno);
	close(data->pipe[1]);
	command = make_command(data->cmd[1]);
	if (command == 0)
		error_print(errno);
	path = path_search(data->path, command[0]);
	if (dup2(data->pipe[0], 0) == -1)
		error_print(errno);
	close(data->pipe[0]);
	if (dup2(fd, 1) == -1)
		error_print(errno);
	close(fd);
	if (execve(path, command, env) == -1)
		error_print(126);
}

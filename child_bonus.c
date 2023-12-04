/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:24:18 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/04 15:01:03 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	make_child(t_data *data, char **av, int i, char **env)
{
	if (i < data->cmd_num - 1)
	{
		if (pipe(data->pipe[i]) == -1)
			error_print(errno);
		data->id[i] = fork();
		if (data->id[i] == 0)
		{
			if (i == 0)
				command_exec_first(data, av, env);
			else
				command_exec_mid(data, i, env);
		}
	}
	else if (i == data->cmd_num - 1)
	{
		data->id[i] = fork();
		if (data->id[i] == 0)
			command_exec_end(data, env);
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
	close(data->pipe[0][0]);
	command = make_command(data->cmd[0]);
	if (command == 0)
		error_print(errno);
	path = path_search(data->path, command[0]);
	if (dup2(fd, 0) == -1)
		error_print(errno);
	close(fd);
	if (dup2(data->pipe[0][1], 1) == -1)
		error_print(errno);
	close(data->pipe[0][1]);
	if (execve(path, command, env) == -1)
		error_print(errno);
}

void	command_exec_mid(t_data *data, int i, char **env)
{
	char	**command;
	char	*path;

	close_pipe(data, i);
	close(data->pipe[i][0]);
	close(data->pipe[i - 1][1]);
	command = make_command(data->cmd[i]);
	if (command == 0)
		error_print(errno);
	path = path_search(data->path, command[0]);
	if (dup2(data->pipe[i - 1][0], 0) == -1)
		error_print(errno);
	close(data->pipe[i - 1][0]);
	if (dup2(data->pipe[i][1], 1) == -1)
		error_print(errno);
	close(data->pipe[i][1]);
	if (execve(path, command, env) == -1)
		error_print(errno);
}

void	command_exec_end(t_data *data, char **env)
{
	char	**command;
	char	*path;
	int		fd;

	close_pipe(data, data->cmd_num - 1);
	fd = open(data->cmd[data->cmd_num],
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		error_print(errno);
	close(data->pipe[data->cmd_num - 2][1]);
	command = make_command(data->cmd[data->cmd_num - 1]);
	if (command == 0)
		error_print(errno);
	path = path_search(data->path, command[0]);
	if (dup2(data->pipe[data->cmd_num - 2][0], 0) == -1)
		error_print(errno);
	close(data->pipe[data->cmd_num - 2][0]);
	if (dup2(fd, 1) == -1)
		error_print(errno);
	close(fd);
	if (execve(path, command, env) == -1)
		error_print(errno);
}

void	close_pipe(t_data *data, int i)
{
	int		j;

	j = 0;
	while (i > 1 && j < i - 1)
	{
		close(data->pipe[j][0]);
		close(data->pipe[j++][1]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:24:18 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/02 18:34:48 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command_exec_first(t_data *data, int fd, char **env)
{
	char	**command;
	char	*path;

	close(data->pipe[0][0]);
	command = ft_split(data->cmd[0], ' ');
	if (command == 0)
		error_print(2);
	path = path_search(data->path, command[0]);
	if (dup2(fd, 0) == -1)
		error_print(1);
	close(fd);
	if (dup2(data->pipe[0][1], 1) == -1)
		error_print(1);
	close(data->pipe[0][1]);
	execve(path, command, env);
}

void	command_exec_mid(t_data *data, int i, char **env)
{
	char	**command;
	char	*path;
	int		j;

	j = 0;
	while (i > 1 && j < i - 2)
	{
		close(data->pipe[j][0]);
		close(data->pipe[j][1]);
		j++;
	}
	close(data->pipe[i][0]);
	close(data->pipe[i - 1][1]);
	command = ft_split(data->cmd[i], ' ');
	if (command == 0)
		error_print(2);
	path = path_search(data->path, command[0]);
	if (dup2(data->pipe[i - 1][0], 0) == -1)
		error_print(1);
	close(data->pipe[i - 1][0]);
	if (dup2(data->pipe[i][1], 1) == -1)
		error_print(1);
	close(data->pipe[i][1]);
	execve(path, command, env);
}

void	command_exec_end(t_data *data, int fd, char **env)
{
	char	**command;
	char	*path;
	int		j;

	j = 0;
	while (data->cmd_num > 2 && j < data->cmd_num - 2)
	{
		close(data->pipe[j][0]);
		close(data->pipe[j][1]);
		j++;
	}
	close(data->pipe[data->cmd_num - 2][1]);
	command = ft_split(data->cmd[data->cmd_num - 1], ' ');
	if (command == 0)
		error_print(2);
	path = path_search(data->path, command[0]);
	if (dup2(data->pipe[data->cmd_num - 2][0], 0) == -1)
		error_print(1);
	close(data->pipe[data->cmd_num - 2][0]);
	if (dup2(fd, 1) == -1)
		error_print(1);
	close(fd);
	execve(path, command, env);
}

void	command_exec_only(t_data *data, int *fd, char **env)
{
	char	**command;
	char	*path;

	command = ft_split(data->cmd[0], ' ');
	if (command == 0)
		error_print(2);
	path = path_search(data->path, command[0]);
	if (dup2(fd[0], 0) == -1)
		error_print(1);
	close(fd[0]);
	if (dup2(fd[1], 1) == -1)
		error_print(1);
	close(fd[1]);
	execve(path, command, env);
}

void	make_child(t_data *data, int *fd, int i, char **env)
{
	if (i < data->cmd_num - 1)
	{
		if (pipe(data->pipe[i]) == -1)
			error_print(1);
		data->id[i] = fork();
		if (data->id[i] == 0)
		{
			if (i == 0)
				command_exec_first(data, fd[0], env);
			else
				command_exec_mid(data, i, env);
		}
	}
	else if (i == data->cmd_num - 1)
	{
		data->id[i] = fork();
		if (data->id[i] == 0 && i != 0)
			command_exec_end(data, fd[1], env);
		else if (data->id[i] == 0 && i == 0)
			command_exec_only(data, fd, env);
	}
}

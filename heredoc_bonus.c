/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:47:48 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/04 18:52:08 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc_name(char **heredoc)
{
	char	*tmp;
	int		i;

	i = 1;
	while (42)
	{
		tmp = ft_itoa(i++);
		if (tmp == 0)
			error_print(errno);
		*heredoc = ft_strjoin("heredoc", tmp, "");
		if (*heredoc == 0)
			error_print(errno);
		if (access(*heredoc, F_OK) != 0)
			break ;
		free(tmp);
		free(*heredoc);
	}
}

void	make_heredoc(char **av, char **heredoc)
{
	char	*tmp;
	char	*endstr;
	int		fd;

	heredoc_name(heredoc);
	fd = open(*heredoc, O_RDWR | O_CREAT, 0644);
	endstr = ft_strjoin(av[2], "\n", "");
	while (42)
	{
		tmp = get_next_line(0);
		if (tmp == 0 || ft_strncmp(tmp, endstr, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			free(endstr);
			break ;
		}
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
	close(fd);
}

void	make_child_heredoc(t_data *data, char *heredoc, char **env)
{
	int	i;

	i = -1;
	while (i++ < data->cmd_num)
	{
		if (i < data->cmd_num - 1)
		{
			if (pipe(data->pipe[i]) == -1)
				error_print(errno);
			data->id[i] = fork();
			if (data->id[i] == 0)
			{
				if (i == 0)
					command_exec_first_heredoc(data, heredoc, env);
				else
					command_exec_mid(data, i, env);
			}
		}
		else if (i == data->cmd_num - 1)
		{
			data->id[i] = fork();
			if (data->id[i] == 0)
				command_exec_end_heredoc(data, env);
		}
	}
}

void	command_exec_first_heredoc(t_data *data, char *heredoc, char **env)
{
	int		fd;
	char	**command;
	char	*path;

	fd = open(heredoc, O_RDONLY);
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

void	command_exec_end_heredoc(t_data *data, char **env)
{
	char	**command;
	char	*path;
	int		fd;

	close_pipe(data, data->cmd_num - 1);
	fd = open(data->cmd[data->cmd_num],
			O_WRONLY | O_APPEND | O_CREAT, 0644);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_setting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:13:01 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/02 18:34:48 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**path_setting(char **env)
{
	char	**env_path;
	int		i;

	i = 0;
	while (*env && ft_strncmp(*env, "PATH", 4) != 0)
		env++;
	if (*env == 0)
		error_print(1);
	while (i++ < 5)
		(*env)++;
	env_path = ft_split(*env, ':');
	if (env_path == 0)
		error_print(2);
	return (env_path);
}

char	*path_search(char **env, char *command)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = ft_strjoin(env[i++], command, "/");
		if (tmp == 0)
			error_print(2);
		if (access(tmp, F_OK) == 0)
			break ;
		free(tmp);
		tmp = 0;
	}
	if (tmp == 0)
		error_print(1);
	return (tmp);
}

int	open_check(int ac, char **av, int *fd, char **heredoc)
{
	int		i;
	char	*tmp;

	fd[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (ft_strncmp("here_doc", av[1], ft_strlen(av[1])) == 0)
	{
		i = 1;
		while (42)
		{
			tmp = ft_itoa(i++);
			if (tmp == 0)
				error_print(2);
			*heredoc = ft_strjoin("heredoc", tmp, "");
			if (*heredoc == 0)
				error_print(2);
			if (access(*heredoc, F_OK) != 0)
				break ;
			free(tmp);
			free(*heredoc);
		}
		fd[0] = open(*heredoc, O_RDWR | O_CREAT, 0644);
		return (1);
	}
	fd[0] = open(av[1], O_RDONLY);
	return (0);
}

void	first_setting(int ac, char **av, t_data *data, char **env)
{
	int	i;

	data->pipe = (int **)malloc(sizeof(int *) * (ac - 4));
	data->id = (pid_t *)malloc(sizeof(pid_t) * (ac - 3));
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
	data->cmd_num = ac - 3;
	data->cmd = av + 2;
}

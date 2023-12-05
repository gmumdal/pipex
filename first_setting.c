/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:13:01 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/05 15:30:52 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_setting(char **av, t_data *data, char **env)
{
	data->pipe = (int *)malloc(sizeof(int) * 2);
	data->id = (pid_t *)malloc(sizeof(pid_t) * 2);
	if (data->pipe == 0 || data->id == 0)
		error_print(errno);
	data->path = path_setting(env);
	data->cmd_num = 2;
	data->cmd = av + 2;
}

char	**path_setting(char **env)
{
	char	**env_path;
	int		i;

	i = 0;
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == 0)
		*env = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:";
	(*env) += 5;
	env_path = ft_split(*env, ':');
	if (env_path == 0)
		error_print(errno);
	return (env_path);
}

char	*path_search(char **env, char *command)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = 0;
	if (ft_strchr(command, '/') && access(command, F_OK) == 0)
		return (command);
	if (ft_strchr(command, '/'))
		command_error(command);
	while (env[i])
	{
		tmp = ft_strjoin(env[i++], command, "/");
		if (tmp == 0)
			error_print(errno);
		if (access(tmp, F_OK) == 0)
			break ;
		free(tmp);
		tmp = 0;
	}
	if (tmp == 0)
		command_error(command);
	return (tmp);
}

void	command_error(char *command)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

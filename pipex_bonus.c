/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:10:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/05 15:14:10 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	int		i;
	t_data	data;
	char	*heredoc;

	if (ac < 5)
		error_print(2);
	heredoc = 0;
	if (ft_strncmp("here_doc", av[1], ft_strlen(av[1])) == 0)
	{
		if (ac < 6)
			error_print(2);
		heredoc_setting(ac, av, &data, env);
		make_heredoc(av, &heredoc);
		make_child_heredoc(&data, heredoc, env);
	}
	else
	{
		first_setting(ac, av, &data, env);
		i = 0;
		while (i < data.cmd_num)
			make_child(&data, av, i++, env);
	}
	exit(ending(&data, heredoc));
}

int	ending(t_data *data, char *heredoc)
{
	int		status;
	int		code;
	int		i;

	i = 0;
	close_pipe(data, data->cmd_num);
	while (i++ < data->cmd_num)
	{
		if (wait(&status) == data->id[data->cmd_num - 1])
			code = WEXITSTATUS(status);
	}
	ending_free(data);
	free(heredoc);
	unlink(heredoc);
	return (code);
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

void	error_print(int flag)
{
	ft_putstr_fd("pipex: ", 2);
	if (flag == 2)
		ft_putstr_fd("input: ", 2);
	ft_putstr_fd(strerror(flag), 2);
	ft_putstr_fd("\n", 2);
	if (flag == 126)
		exit(126);
	exit(1);
}

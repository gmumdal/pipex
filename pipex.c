/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:10:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/03 20:18:42 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		i;
	int		code;
	int		status;
	t_data	data;

	if (ac != 5)
		error_print(5);
	first_setting(av, &data, env);
	i = 0;
	while (i < data.cmd_num)
		make_child(&data, av, i++, env);
	close(data.pipe[0]);
	close(data.pipe[1]);
	i = 0;
	while (i++ < 2)
	{
		if (wait(&status) == data.id[1])
			code = WEXITSTATUS(status);
	}
	ending_free(&data);
	exit(code);
}

void	ending_free(t_data *data)
{
	int	i;

	i = 0;
	while (data->path[i] != 0)
		free(data->path[i++]);
	free(data->path);
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
	exit(1);
}

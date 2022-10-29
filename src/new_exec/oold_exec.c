/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 05:19:20 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/29 05:41:59 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redir(int *fd, t_data *data)
{
	close(fd[0]);
	if (data->out == 1)
		dup2(fd[1], 1);
	else
		close (fd[1]);
}



int	ft_cmd(t_data *data)
{
	char	*path;

	if (data->new_args[0][0] == '/' || data->new_args[0][0] == '.')
		path = data->new_args[0];
	else
		path = ft_get_path(data->new_args[0], data->env);
	if (!path)
	{
		printf("Error cmd not found\n");
		exit (1);
	}
	execve(path, data->new_args, data->env);
	printf("Can't access command %s\n", path);
	return (-1);
		
}

int	ft_pipex(t_data *data)
{
	pid_t	pid;
	int		fd[2];
	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		ft_redir(fd, data);
		ft_cmd(data);
		return (0);
	}
	close(fd[1]);
	close(fd[0]);
	dup2(fd[0], 0);
	return (0);
}

void	ft_last_child(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		ft_cmd(data);
	else
		wait(NULL);
	return ;
}

void	ft_loop_exec(t_data *data)
{
	if (data->out > STDOUT_FILENO)
		dup2(data->out, STDOUT_FILENO);
	if (data->in > STDIN_FILENO)
		dup2(data->in, STDIN_FILENO);
	if (data->next)
		ft_pipex(data);
	else
		ft_last_child(data);
}

void	ft_lauch_exec(t_data *data)
{
	t_data *tmp;

	tmp = data;
	while (tmp)
	{
		ft_loop_exec(tmp);
		if (tmp->out > 1)
			dup2(data->out, 1);
		tmp = tmp->next;
		if (tmp && tmp->in > 0)
			dup2(data->in, 0);
	}
}
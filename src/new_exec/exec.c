/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:19:10 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/04 07:19:50 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_clean(t_env *mini, t_env *origin, t_data *data)
{
	ft_clear_data_tab(data, 1);
	ft_clear_data_tab(data, 0);
	lst_freeall(mini);
	lst_freeall(origin);
	ft_free(0, &data);
	exit(1);
}

int	ft_cmd(t_data *data, t_env *mini, t_env *origin)
{
	char	*path;

	if (data->new_args[0][0] == '/' || data->new_args[0][0] == '.' || data->code)
		path = ft_strdup(data->new_args[0]);
	else
		path = ft_get_path(data->new_args[0], data->env);
	if (!path)
		return (-1);
	if (data->in < 0 || data->out < 0)
		return (free(path), -1);
	if (data->in > STDIN_FILENO)
		dup2(data->in, STDIN_FILENO);
	if (data->out > STDOUT_FILENO)
		dup2(data->out, STDOUT_FILENO);
	if (data->code)
		ft_builtin(data, mini, origin);
	execve(path, data->new_args, data->env);
	return (free(path), -1);
}

int	ft_fork(t_env *mini, t_env *origin, t_data *data)
{
	int	fd[2];
	int	pid;

	(void)mini;
	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid != 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
		close(fd[0]);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_cmd(data, mini, origin);
		close(fd[1]);
		return (-1);
	}
	return (0);
}

int	ft_last_child(t_data *data, t_env *mini, t_env *origin)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ft_cmd(data, mini, origin) < 0)
		{
			if (data->new_args[0])
				printf("%s : command not found\n", data->new_args[0]);
			return (-1);
		}
	}
	else
		wait(NULL);
	return (0);
}

void	ft_exe(t_env *mini, t_env *origin, t_data *data)
{
	int		out;
	int		in;
	t_data	*tmp;

	(void)origin;
	(void)mini;
	in = dup(0);
	out = dup(1);
	tmp = data;
	while (tmp && tmp->next)
	{
		if (ft_fork(mini, origin, tmp) < 0)
		{
			dup2(out, STDOUT_FILENO);
			printf("%s : command not found\n", tmp->new_args[0]);
			ft_exit_clean(mini, origin, data);
			exit(1);
		}
		tmp = tmp->next;
	}
	if (ft_last_child(tmp, mini, origin) < 0)
		ft_exit_clean(mini, origin, data);
	ft_clear_data_tab(data, 1);
	ft_clear_data_tab(data, 0);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(in);
	close(out);
}

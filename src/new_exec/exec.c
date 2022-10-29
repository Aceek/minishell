/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:19:10 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/29 06:39:14 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_list(t_data *data)
{
	int	i;
	t_data *tmp;

	tmp = data;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
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
		printf("%s : command not found\n", data->new_args[0]);
		// free_tab(data->new_args);
		return (-1); // a changer par un return 
	}
	if (data->in > 0)
		dup2(data->in, 0);
	if (data->out > 1)
		dup2(data->out, 1);
	execve(path, data->new_args, data->env);
	printf("can't access command\n");
	return (-1);
	
}

int	ft_fork(t_env *mini, t_data *data)
{
	int	fd[2];
	int	pid;
	(void)mini;

	pipe(fd);
	pid = fork();
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
		ft_cmd(data);
		return (close(fd[1]), -1);
	}
	return (0);
}

int	ft_last_child(t_data *data)
{
	int	pid;
	pid = fork();
	if (pid == 0)
	{
		if (ft_cmd(data) < 0)
			exit (-1); // error code ? need exit clean
	}
	else
		wait(NULL);
	return (0);
}

void	ft_exe(t_env *mini, t_env *origin, t_data *data)
{
	(void)origin;
	(void)mini;
	int	out;
	int	in;

	in = dup(0);
	out = dup(1);
	data->a = in;
	data->b = out;

	t_data *tmp;

	tmp = data;
	while (tmp && ft_count_list(tmp) >= 2)
	{
		if (ft_fork(mini, tmp) == -1)
		{
			printf("error tmp fork\n\n");		
			return ;
		}
		tmp = tmp->next;
	}
	ft_last_child(tmp);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(out);
	close(in);
}
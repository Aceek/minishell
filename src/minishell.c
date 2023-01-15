/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/14 02:00:03 by pbeheyt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

void	ft_shlvl(t_env *mini)
{
	t_env	*tmp;
	int		i;

	tmp = mini;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, "SHLVL=", 6))
		{
			i = ft_strlen(tmp->line);
			tmp->line[i - 1]++;
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_init_main(t_data *data, t_env **mini, char **env)
{
	if (!isatty(0))
	{
		write(2, "minishell : standard input need to be term\n", 43);
		exit (1);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->fd_out = 1;
	data->env = env;
	*mini = ft_create_env(env);
	if (!*mini)
		exit (1);
	ft_shlvl(*mini);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, ft_signal_newline);
}

void	ft_printf_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	if (!cmd)
		return ;
	tmp = cmd;
	while (tmp->next)
	{
		i = -1;
		while (tmp->tab[++i])
			printf("args %d : %s \n", i, tmp->tab[i]);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_init_main(&data, &data.mini, env);
	while (ac > 0 && av[0])
	{
		data.input = readline("\033[1;35m\033[1m minishell ▸ \033[0m");
		if (!data.input)
		{
			write(1, "exit\n", 5);
			free(data.input);
			ft_exit_clean(data.mini, data.head_cmd, 1);
		}
		else if (data.input && data.input[0])
		{
			add_history(data.input);
			if (!check_error(data.input))
			{
				parse_input(&data);
				ft_exe(data.mini, data.head_cmd, data.file_error);
			}
			data.head_cmd = NULL;
			free(data.input);
		}
	}
	return (lst_freeall(data.mini), 0);
}

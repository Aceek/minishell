/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/26 03:04:55 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

t_env	*ft_create_env(char **env)
{
	int		i;
	t_env	*mini;

	i = -1;
	mini = malloc(sizeof(t_env));
	if (!mini)
		exit(1);
	mini->next = NULL;
	mini->line = NULL;
	while (env && env[++i])
		lst_addback(mini, env[i]);
	return (mini);
}

void	ft_signal_newline(int unused)
{
	(void)unused;
	rl_on_new_line();
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_init_main(t_data *data, t_env **mini, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->env = env;
	data->curr_fd_out = 1;
	*mini = ft_create_env(env);
	if (!*mini)
		exit (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_newline);
}

void	ft_printf_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		i = -1;
		while (tmp->tab[++i])
			printf("args %d : %s ", i, tmp->tab[i]);
		printf("\n");
		printf("fd_in : %d  fd_out : %d\n", tmp->fd_in, tmp->fd_out);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.mini = NULL;
	ft_init_main(&data, &data.mini, env);
	while (ac > 0 && av[0])
	{
		data.input = readline("mini> ");
		if (!data.input)
		{
			printf("exit\n");
			free(data.input);
			ft_exit_clean(data.mini, data.head_cmd, 1);
		}
		else if (data.input && data.input[0])
		{
			add_history(data.input);
			parse_input(&data);
			// ft_printf_list(data.head_cmd);
			ft_exe(data.mini, data.head_cmd);
			data.head_cmd = NULL;
			free(data.input);
		}
	}
	return (lst_freeall(data.mini), 0);
}

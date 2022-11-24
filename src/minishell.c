/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/24 06:03:34 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_init_main(t_data *data, t_env *mini, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->env = env;
	data->curr_fd_out = 1;
	mini = ft_create_env(env);
	if (!mini)
		exit (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_newline);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_env	*mini;

	mini = NULL;
	ft_init_main(&data, mini, env);
	while (ac > 0 && av[0])
	{
		data.input = readline("mini> ");
		if (!data.input)
		{
			printf("exit\n");
			free(data.input);
			ft_exit_clean(mini, data.head_cmd);
		}
		else if (data.input && data.input[0])
		{
			add_history(data.input);
			parse_input(&data);
			ft_exe(mini, data.head_cmd);
			data.head_cmd = NULL;
			free(data.input);
		}
	}
	return (lst_freeall(mini), 0);
}

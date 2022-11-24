/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/24 05:07:29 by pbeheyt          ###   ########.fr       */
=======
/*   Updated: 2022/11/24 05:26:52 by ilinhard         ###   ########.fr       */
>>>>>>> exec
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_create_env(char **env)
{
	int		i;
	t_env	*mini;

	i = -1;
	mini = malloc(sizeof(t_env));
	if (!mini)  // si le malloc plante il faut stop le programme sinon segfault
		return (NULL);
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

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	data.env = env;
	data.curr_fd_out = 1;
	data.mini = ft_create_env(env);
	if (!data.mini)
		exit (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_newline);
	while (ac > 0 && av[0])
	{
		data.input = readline("mini> ");
		if (!data.input)
		{
			printf("exit\n");
			free(data.input);
			ft_exit_clean(data.mini ,data.head_cmd);
		}
		else if (data.input && data.input[0])
		{
			add_history(data.input);
			parse_input(&data);
			ft_exe(data.mini, data.head_cmd);
			data.head_cmd = NULL;
			free(data.input);
		}
	}
	return (lst_freeall(data.mini), 0);
}

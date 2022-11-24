/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/24 03:49:10 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_list_cmd(t_data *data)
// {
// 	t_cmd	*tmp;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	tmp = data->head_cmd;
// 	while (tmp)
// 	{
// 		i = -1;
// 		printf("cmd %d\n", ++j);
// 		printf("built in %d\n", tmp->builtin);
// 		while (tmp->tab[++i])
// 			printf("tab %d -> %s\n", i, tmp->tab[i]);
// 		tmp = tmp->next;
// 	}
// }

// int	main(int ac, char **av, char **env)
// {
// 	t_data	data;

// 	(void)ac;
// 	(void)av;
// 	ft_memset(&data, 0, sizeof(t_data));
// 	data.env = env;
// 	data.curr_fd_out = 1;
// 	while (1)
// 	{
// 		data.input = readline("mini> ");
// 		parse_input(&data);
// 		print_list_cmd(&data);
// 		ft_listclear(&data.list_cmd);
// 	}
// 	return (0);
// }

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


int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_env	*mini;

	ft_memset(&data, 0, sizeof(t_data));
	data.env = env;
	data.curr_fd_out = 1;
	mini = ft_create_env(env);
	if (!mini)
		exit (1);
	int	i = 0;
	while (ac > 0 && av[0])
	{
		data.input = readline("mini> ");
		if (i == 3)
		{
			free(data.input);
			data.input = NULL;
		}
		if (!data.input)
		{
			printf("exit\n");
			free(data.input);
			ft_exit_clean(mini ,data.head_cmd);
		}
		else if (data.input && data.input[0])
		{
			add_history(data.input);
			parse_input(&data);
			ft_exe(mini, data.head_cmd);
			data.head_cmd = NULL;
			free(data.input);
		}
		i++;
	}
	return (lst_freeall(mini), 0);
}

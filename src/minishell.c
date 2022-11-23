/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/23 04:14:15 by ilinhard         ###   ########.fr       */
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
	(void)env;

	i = 0;

	mini = malloc(sizeof(t_env));
	if (!mini)  // si le malloc plante il faut stop le programme sinon segfault
		return (NULL);
	mini->next = NULL;
	mini->line = NULL;
	return (mini);
}


int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_env	*mini;
	t_env	*origin;

	ft_memset(&data, 0, sizeof(t_data));
	data.env = env;
	data.curr_fd_out = 1;
	origin = ft_create_env(env);
	mini = ft_create_env(env);
	while (ac > 0 && av[0])
	{
		data.input = readline("mini> ");
		if (!data.input)
		{
			printf("exit\n");
			free(data.input);
			exit(1); // free function
		}
		else if (data.input && data.input[0])
		{
			add_history(data.input);
			parse_input(&data);
			if (!mini)
				exit (1);
			// print_list_cmd(&data); // provisoire
			ft_exe(mini, origin, data.head_cmd);
			ft_listclear(&data.head_cmd);
			free(data.input);
		}
	}
	return (0); //return clear 2 list t_env mini + t_env origin
}

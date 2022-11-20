/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/20 03:26:33 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	print_list_cmd(t_data *data)
{
	t_cmd	*tmp;
	int		i;
	// int		j;
	
	// j = 0;
	tmp = data->list_cmd;
	while (tmp)
	{
		i = -1;
		// printf("cmd %d\n", ++j);
		// printf("built in %d\n", tmp->built_in);
		while (tmp->tab[++i])
			printf("tab %d -> %s\n", i, tmp->tab[i]);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	
	(void)ac;
	(void)av;
	(void)env;
	ft_memset(&data, 0, sizeof(t_data));
	data.list_cmd = NULL;
	data.env = env;
	while (1)
	{
		data.input = readline("mini> ");
		parse_input(&data);
		print_list_cmd(&data);
	}
	return (0);	
}


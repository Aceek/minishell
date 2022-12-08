/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/08 02:21:10 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*create_buffer(void)
{
	char	*buf;

	buf = malloc(sizeof(char));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	return (buf);
}

void	free_all_exit(t_data *data)
{
	if (data->buf)
		free(data->buf);
	if (data->redir_arg)
		free(data->redir_arg);
	if (data->path)
		free(data->path);
	ft_exit_clean(data->mini, data->head_cmd, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/09 02:59:51 by pbeheyt          ###   ########.fr       */
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

char	*add_char(t_data *data, char *buf, char c)
{
	char	*tmp;

	tmp = ft_charjoin(buf, c);
	if (!tmp)
		return (free_all_exit(data, 1), NULL);
	free(buf);
	buf = tmp;
	return (buf);
}

char	*convert_input(t_data *data, char *buf, char *str, int *i)
{
	char	*var;
	char	*tmp;

	if (str[*i] == '$' && check_quote_pos(str, *i) != 1)
	{
		if (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_'
			&& str[*i + 1] != '?')
			return (add_char(data, buf, str[*i]));
		var = get_dollar(str, i, data->mini);
		if (!var)
			return (free(var), buf);
		tmp = ft_strjoin(buf, var);
		if (!tmp)
			return (free_all_exit(data, 1), NULL);
		free(buf);
		free(var);
		buf = tmp;
	}
	else
		buf = add_char(data, buf, str[*i]);
	return (buf);
}

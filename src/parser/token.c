/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/12 01:13:17 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_builtin_code(char *str)
{
	if (!str)
		return (NOT_BUILT_IN);
	if (!ft_strncmp(str, "echo", 4) && !str[4])
		return (ECH);
	if (!ft_strncmp(str, "pwd", 3) && !str[3])
		return (PWD);
	if (!ft_strncmp(str, "cd", 2) && !str[2])
		return (CD);
	if (!ft_strncmp(str, "export", 6) && !str[6])
		return (EXPORT);
	if (!ft_strncmp(str, "unset", 5) && !str[5])
		return (UNSET);
	if (!ft_strncmp(str, "env", 3) && !str[3])
		return (ENV);
	if (!ft_strncmp(str, "exit", 4) && !str[4])
		return (EXIT);
	return (NOT_BUILT_IN);
}

int	get_token_code(char *str, int *i)
{
	if (str[*i] && str[*i + 1])
	{
		if (check_quote_pos(str, *i) == 0 && check_quote_pos(str, *i + 1) == 0)
		{
			if (!ft_strncmp(str + *i, ">>", 2))
				return (*i += 1, DGREAT);
			if (!ft_strncmp(str + *i, "<<", 2))
				return (*i += 1, DLESS);
		}
	}
	if (check_quote_pos(str, *i) == 0)
	{
		if (!ft_strncmp(str + *i, "<", 1))
			return (*i += 0, LESS);
		if (!ft_strncmp(str + *i, ">", 1))
			return (*i += 0, GREAT);
		if (!ft_strncmp(str + *i, "|", 1))
			return (*i += 0, PIPE);
	}
	return (NOT_TOKEN);
}

int	is_token(char *str, int i)
{
	if ((str[i] == '|' || str[i] == '<' || str[i] == '>')
		&& check_quote_pos(str, i) == 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/23 03:30:28 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_quote(bool *quote)
{
	if (*quote == false)
		*quote = true;
	else if (*quote == true)
		*quote = false;
}

int	check_quote_error(char *str)
{
	bool	simple_quote;
	bool	double_quote;
	int		i;

	if (!str)
		return (-1);
	simple_quote = false;
	double_quote = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && double_quote == false)
			update_quote(&simple_quote);
		if (str[i] == '\"' && simple_quote == false)
			update_quote(&double_quote);
	}
	if (double_quote == true)
		return (2);
	if (simple_quote == true)
		return (1);
	return (0);
}

int	check_quote_pos(char *str, int pos)
{
	bool	simple_quote;
	bool	double_quote;
	int		i;

	if (!str)
		return (-1);
	simple_quote = false;
	double_quote = false;
	i = -1;
	while (++i < pos)
	{
		if (str[i] == '\'' && double_quote == false)
			update_quote(&simple_quote);
		if (str[i] == '\"' && simple_quote == false)
			update_quote(&double_quote);
	}
	if (str[i] != '\"' && double_quote == true)
		return (2);
	if (str[i] != '\'' && simple_quote == true)
		return (1);
	return (0);
}

int	check_token(char *str, int *i)
{
	if (str[*i + 1])
	{
		if (!check_quote_pos(str, *i) && !check_quote_pos(str, *i + 1))
		{
			if (!ft_strncmp(str + *i, ">>", 2))
				return (*i += 2, DGREAT);
			if (!ft_strncmp(str + *i, "<<", 2))
				return (*i += 2, DLESS);
		}
	}
	if (!check_quote_pos(str, *i))
	{
		if (!ft_strncmp(str + *i, "<", 1))
			return (*i += 1, LESS);
		if (!ft_strncmp(str + *i, ">", 1))
			return (*i += 1, GREAT);
		if (!ft_strncmp(str + *i, "|", 1))
			return (*i += 1, PIPE);
	}
	return (NOT_TOKEN);
}

int	check_built_in(char *str)
{
	if (!str)
		return (NOT_BUILT_IN);
	if (!ft_strncmp(str, "echo", ft_strlen("echo")))
		return (ECH);
	if (!ft_strncmp(str, "pwd", ft_strlen("pwd")))
		return (PWD);
	if (!ft_strncmp(str, "cd", ft_strlen("cd")))
		return (CD);
	if (!ft_strncmp(str, "export", ft_strlen("export")))
		return (EXPORT);
	if (!ft_strncmp(str, "unset", ft_strlen("unset")))
		return (UNSET);
	if (!ft_strncmp(str, "env", ft_strlen("env")))
		return (ENV);
	if (!ft_strncmp(str, "exit", ft_strlen("exit")))
		return (EXIT);
	return (NOT_BUILT_IN);
}

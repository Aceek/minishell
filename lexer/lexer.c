/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/20 05:14:48 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void update_quote(bool *quote)
{
	if (*quote == false)
		*quote = true;
	else if (*quote == true)
		*quote = false;
}

int check_quote_error(char *str)
{
	bool	simple_quote;
	bool	double_quote;
	int		i;
	
	if (!str)
		return (-1);
	simple_quote = false;
	double_quote = false;
	i = -1;
	while(str[++i])
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

int check_quote_pos(char *str, int pos)
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
			if (ft_strncmp(str + *i, ">>", 2))
				return (*i += 2, DGREAT);
			if (ft_strncmp(str + *i, "<<", 2))
				return (*i += 2, DLESS);
		}
	}
	if (!check_quote_pos(str, *i))
	{
		if (ft_strncmp(str + *i, "<", 1))
			return (*i += 1, LESS);
		if (ft_strncmp(str + *i, ">", 1))
			return (*i += 1, GREAT);
		if (ft_strncmp(str + *i, "|", 1))
			return (*i += 1, PIPE);
	}
	return (NOT_TOKEN);
}

int	get_var_len(char *str, int i)
{
	int var_len;
	
	var_len = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{	
		var_len += 1;
		i++;
	}
	return (var_len);
}

char *get_var_val(char *var_name, int var_len, char **env)
{
	int	l;

	l = -1;
	while (env[++l])
	{
		if (ft_strnstr(env[l], var_name, var_len))
			return (ft_cpy(env[l], var_len + 1));
	}
	return (NULL);
}

char *dollar_handler(char *str, int *i, char **env)
{
	int		var_len;
	char	*var_name;
	char	*var_val;

	var_len = 0;
	if (!str[*i + 1])
		return (NULL);
	// else if (!str[*i + 1] == '?')
		//...Stores the exit value of the last command that was executed
	else
	{	
		var_len = get_var_len(str, *i + 1);
		var_name = ft_strncpy_from (str, *i + 1, var_len);
		var_val = get_var_val(var_name, var_len, env);
		// printf("i AV = %d\n", *i);
		*i += var_len;
		// printf("i AP = %d\n", *i);
		// printf("var_len = %d\n", var_len);
		// printf("var_name = %s\n", var_name);
		// printf("var_val = %s\n", var_val);
	}	
	return (var_val);
}



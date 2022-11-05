/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/05 07:03:32 by pbeheyt          ###   ########.fr       */
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

int check_quote(char *str, int pos)
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
		if (!check_quote(str, *i) && !check_quote(str, *i + 1))
		{
			if (ft_strncmp(str + *i, ">>", 2))
			{	
				*i += 1;
				return (DLESS);
			}
			if (ft_strncmp(str + *i, "<<", 2))
			{	
				*i += 1;
				return (DGREAT);
			}
		}
	}
	if (!check_quote(str, *i))
	{
		if (ft_strncmp(str + *i, "<", 1))
			return (LESS);
		if (ft_strncmp(str + *i, ">", 1))
			return (GREAT);
		if (ft_strncmp(str + *i, "|", 1))
			return (PIPE);
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

char	*get_var_name(char *str, int pos, int len)
{
	char	*var_name;
	int		i;
	
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < len)
		var_name[i++] = str[pos++];
	var_name[i] = 0;
	return (var_name);
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
		var_name = get_var_name (str, *i + 1, var_len);
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

char *convert_input(t_data *data)
{
	int		i;
	char	*input2;
	
	
	input2 = malloc(sizeof(char));
	input2[0] = 0;
	i = -1;
	while (data->input[++i])
	{
		if (check_token(data->input, &i))
		{
			printf("input avant split: %s\n",input2);
			add_cmd(data, input2);
			free(input2);
			input2 = malloc(sizeof(char));
			input2[0] = 0;
			//parser input2 dans uns struct qui contient tableau ac commande en 0 + args 
		}
		else if (data->input[i] == '$' && check_quote(data->input, i) != 1)
			input2 = ft_strjoin(input2, dollar_handler(data->input, &i, data->env));
		else
			input2 = ft_strjoin2(input2, data->input[i]);
	}
	return (input2);
	}

static void	print_list_cmd(t_data *data)
{
	t_cmd	*tmp;
	int		i;
	int		j;
	
	j = 0;
	tmp = data->list_cmd;
	i = -1;
	while (tmp)
	{
		while (tmp->tab[++i])
			printf("tab %d -> %s\n", i, tmp->tab[i]);
		tmp = tmp->next;
		printf("cmd %d\n", ++j);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input2;
	t_data	data;
	// int		i;
	
	(void)ac;
	(void)av;
	(void)env;
	ft_memset(&data, 0, sizeof(t_data));
	data.list_cmd = NULL;
	data.env = env;
	while (1)
	{
		data.input = readline("mini> ");
		// i = -1;
		// while (input[++i])
		// {
		// 	printf("P char : %c | quote : %d\n", input[i], quote_value(input, i));
		// 	printf("R char : %c | quote : %d\n", input[i], is_inquotes(input, i));
		// 	printf("\n");
		// }
		input2 = convert_input(&data);
		printf("%s\n", input2);
		print_list_cmd(&data);
	}
	return (0);	
}


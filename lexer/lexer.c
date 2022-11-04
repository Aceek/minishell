/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/04 01:01:56 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void update_quote(bool *quote)
{
	if (*quote == false)
		*quote = true;
	else if (*quote == true)
		*quote = false;
}

static int quote_value(char *str, int pos)
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

// static char	**tokens_list(void)
// {
// 	static char	*tokens_list[5] = {
// 		"<",
// 		"<<",
// 		">",
// 		">>",
// 		"|",
// 	};

// 	return (tokens_list);
// }

// static bool check_token(char *str)
// {
	
// }

// int get_next_length(char *str, char *charset)
// {
	// incremente i tant que cest pas charset interdit	
// }



char    *ft_strnstr(const char *s1, const char *to_find, size_t n)
{
    size_t    i;
    size_t    j;

    i = 0;
    if (*to_find == '\0' || to_find == NULL)
        return ((char *)s1);
    while (s1[i] && i < n)
    {
        j = 0;
        while (s1[i + j] == to_find[j] && j + i < n)
        {
            j++;
            if (to_find[j] == '\0')
                return ((char *)&s1[i]);
        }
        i++;
    }
    return (NULL);
}

char    *ft_cpy(char *src, int skip)
{
    int		i;
    int		max_len;
    char	*dst;

    i  = 0;
    while (src[i])
        i++;
    max_len = i - skip;
    dst = malloc(sizeof(char) * (i - skip + 1));
    if (!dst)
        return (NULL);
    i = 0;
    while (src && src[i] && i < max_len)
    {
        dst[i] = src[i + skip];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

// char *get_var(char *str, int pos, char **env, int var_len)
// {
// 	int	l;
// 	int i;
// 	int	j;

// 	l = -1;
// 	i = pos;
// 	while (env[++l])
// 	{
// 		j = 0;
// 		while (j < var_len)
// 		{
// 			if (str[i++] == env[l][j])
// 				j++;
// 			else
// 			{
// 				i = pos;
// 				break ;
// 			}
// 			if (j == var_len)
// 				return (ft_cpy(env[l], var_len + 1));
// 		} 
// 	}
// 	return (NULL);
// }

int	get_var_len(char *str, int i)
{
	int var_len;
	
	var_len = 0;
	while (str[i] != ' ' && str[i] != '\0')
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
		printf("i AV = %d\n", *i);
		*i += var_len;
		printf("i AP = %d\n", *i);
		printf("var_len = %d\n", var_len);
		printf("var_name = %s\n", var_name);
		printf("var_val = %s\n", var_val);
	}	
	return (var_val);
}

char *convert_input(char *input, char **env)
{
	int		i;
	char	*input2;
	
	
	input2 = malloc(sizeof(char));
	input2[0] = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$' && quote_value(input, i) != 1)
			input2 = ft_strjoin(input2, dollar_handler(input, &i, env));
		else
			input2 = ft_strjoin2(input2, input[i]);
	}
	return (input2);
	}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*input2;
	// int		i;
	
	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("mini> ");
		// i = -1;
		// while (input[++i])
		// {
		// 	printf("P char : %c | quote : %d\n", input[i], quote_value(input, i));
		// 	printf("R char : %c | quote : %d\n", input[i], is_inquotes(input, i));
		// 	printf("\n");
		// }
		input2 = convert_input(input, env);
		printf("%s\n", input2);
	}
	return (0);	
}


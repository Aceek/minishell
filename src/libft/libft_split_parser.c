/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_split_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:11:57 by ilinhard          #+#    #+#             */
/*   Updated: 2022/12/11 03:01:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_del(char *str, int i)
{
	if ((ft_isspace(str[i]) || str[i] == '\0') && check_quote_pos(str, i) == 0)
		return (1);
	return (0);
}

int	count_args(char *str)
{
	int	nb_args;
	int	i;

	nb_args = 0;
	i = -1;
	while (str[++i])
	{
		if (!is_del(str, i) && is_del(str, i + 1))
			nb_args += 1;
	}
	return (nb_args);
}

char	*cpy_no_quotes(char *cpy, char *str, int pos, int len)
{
	int	i;

	i = -1;
	while (i < len)
	{
		if (is_quote(str, pos))
		{	
			pos++;
			len--;
		}
		else
			cpy[++i] = str[pos++];
	}
	cpy[i] = '\0';
	return (cpy);
}

// static char	*fill_line(char *str, char *line, int len, int *i)
// {
// 	int	j;

// 	j = -1;
// 	while (j < len)
// 	{
// 		if (is_quote(str, *i))
// 		{	
// 			*i += 1;
// 			len--;
// 		}
// 		else
// 		{
// 			line[++j] = str[*i];
// 			*i += 1;
// 		}
// 	}
// 	line[j] = '\0';
// 	return (line);
// }

int	fill_tab(char **tab, char *str, int args)
{
	int		i;
	int		len;
	int		l;

	i = 0;
	l = -1;
	while (++l < args)
	{
		while (is_del(str, i))
			i++;
		len = 0;
		while (!is_del(str, i + len))
			len++;
		tab[l] = malloc(sizeof(char) * (len + 1));
		if (!tab[l])
			return (1);
		tab[l] = cpy_no_quotes(tab[l], str, i, len);
		i += len;
		// tab[l] = fill_line(str, tab[l], len, &i);
	}
	return (0);
}

char	**ft_split_parser(char *str)
{
	char	**tab;
	int		args;

	if (!str)
		return (0);
	args = count_args(str);
	tab = malloc(sizeof(char *) * (args + 1));
	if (tab == 0)
		return (0);
	tab[args] = 0;
	if (fill_tab(tab, str, args))
		return (free_tab(tab), NULL);
	return (tab);
}

// static int	is_del(char *str, int i)
// {
// 	if ((ft_isspace(str[i]) || str[i] == '\0') && check_quote_pos(str, i) == 0)
// 		return (1);
// 	return (0);
// }

// static int	count_args(char *str)
// {
// 	int	nb_args;
// 	int	i;

// 	nb_args = 0;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (!is_del(str, i) && is_del(str, i + 1))
// 			nb_args += 1;
// 	}
// 	return (nb_args);
// }

// static char	*fill_line(char *str, char *line, int len, int *i)
// {
// 	int	j;

// 	j = -1;
// 	while (j < len)
// 	{
// 		if (is_quote(str, *i))
// 		{	
// 			*i += 1;
// 			len--;
// 		}
// 		else
// 		{
// 			line[++j] = str[*i];
// 			*i += 1;
// 		}
// 	}
// 	line[j] = '\0';
// 	return (line);
// }

// static int	fill_tab(char **tab, char *str, int args)
// {
// 	int		i;
// 	int		len;
// 	int		l;

// 	i = 0;
// 	l = -1;
// 	while (++l < args)
// 	{
// 		while (is_del(str, i))
// 			i++;
// 		len = 0;
// 		while (!is_del(str, i + len))
// 			len++;
// 		tab[l] = malloc(sizeof(char) * (len + 1));
// 		if (!tab[l])
// 			return (1);
// 		tab[l] = fill_line(str, tab[l], len, &i);
// 	}
// 	return (0);
// }

// char	**ft_split_parser(char *str)
// {
// 	char	**tab;
// 	int		args;

// 	if (!str)
// 		return (0);
// 	args = count_args(str);
// 	tab = malloc(sizeof(char *) * (args + 1));
// 	if (tab == 0)
// 		return (0);
// 	tab[args] = 0;
// 	if (fill_tab(tab, str, args))
// 		return (free_tab(tab), NULL);
// 	return (tab);
// }
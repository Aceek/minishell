/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_split_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:11:57 by ilinhard          #+#    #+#             */
/*   Updated: 2022/12/06 22:53:54 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_del(char c)
{
	if (ft_isspace(c) || c == 0)
		return (1);
	return (0);
}

static int	count_args(char *str)
{
	int	nb_args;
	int	i;

	nb_args = 0;
	i = -1;
	while (str[++i])
	{
		if (!is_del(str[i]) && is_del(str[i + 1]))
			nb_args += 1;
	}
	return (nb_args);
}

static void	free_tab(char **tab)
{	
	int	i;

	i = 0;
	while (tab[i] != 0)
		free(tab[i++]);
	free (tab);
}

static int	fill_tab(char **tab, char *str, int args)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	k = 0;
	l = 0;
	while (l < args)
	{
		while (is_del(str[i]) == 1)
			i++;
		j = 0;
		while (is_del(str[j + i]) == 0)
			j++;
		tab[l] = malloc(sizeof(char) * (j + 1));
		if (tab[l] == 0)
			return (-1);
		k = 0;
		while (k < j)
			tab[l][k++] = str[i++];
		tab[l][k] = 0;
	l++;
	}
	return (1);
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
	if (fill_tab(tab, str, args) == -1)
		return (free_tab(tab), NULL);
	return (tab);
}
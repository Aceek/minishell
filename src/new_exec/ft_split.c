/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:39:35 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/28 04:17:17 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_charset(char const s, char c)
{
	if (s == '\0' || s == c)
		return (1);
	return (0);
}

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (ft_charset(s[i], c) == 0 && ft_charset(s[i + 1], c) == 1)
			words++;
		i++;
	}
	return (words);
}

void	ft_add_words(char *dest, const char *src, char c)
{
	int	i;

	i = 0;
	while (ft_charset(src[i], c) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_add_to_tab(char **tab, const char *s, char c)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (ft_charset(s[i], c))
			i++;
		else
		{
			j = 0;
			while (ft_charset(s[i + j], c) == 0)
				j++;
			tab[words] = malloc(sizeof(char) * (j + 1));
			ft_add_words(tab[words], &s[i], c);
			i = j + i;
			words++;
		}
	}
}

char	**ft_split2(char const *s, char c)
{
	int		words;
	char	**tab;

	words = 0;
	words = ft_count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	tab[words] = 0;
	ft_add_to_tab(tab, s, c);
	return (tab);
}

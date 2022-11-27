/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:39:35 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/27 06:27:56 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_charset(char const s, char *charset)
{
	int	i;

	i = 0;
	while (charset && charset[i])
	{
		if (charset[i] == s)
			return (1);
		i++;
	}
	if (s == '\0')
		return (1);
	return (0);
}

int	ft_count_words(char const *s, char *charset)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (ft_charset(s[i], charset) == 0
			&& ft_charset(s[i + 1], charset) == 1)
			words++;
		i++;
	}
	return (words);
}

void	ft_add_words(char *dest, const char *src, char *charset)
{
	int	i;

	i = 0;
	while (ft_charset(src[i], charset) == 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_add_to_tab(char **tab, const char *s, char *charset)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (ft_charset(s[i], charset))
			i++;
		else
		{
			j = 0;
			while (ft_charset(s[i + j], charset) == 0)
				j++;
			tab[words] = malloc(sizeof(char) * (j + 1));
			ft_add_words(tab[words], &s[i], charset);
			i = j + i;
			words++;
		}
	}
}

char	**ft_split2(char const *s, char *charset)
{
	int		words;
	char	**tab;

	words = 0;
	words = ft_count_words(s, charset);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
	{
		ft_clear_tab(tab);
		return (NULL);
	}
	tab[words] = 0;
	ft_add_to_tab(tab, s, charset);
	return (tab);
}

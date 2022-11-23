/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/23 23:19:17 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_charjoin(char *s1, char c)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1) + 1;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	str[i] = 0;
	return (str);
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 			i++;
// 	if (i == ft_strlen(s1))
// 		return (1);
// 	return (0);
// }

// int	ft_strncmp(char *s1, char *s2, size_t n)
// {
// 	size_t	i;

// 	if (!n)
// 		return (0);
// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
// 			i++;
// 	if (i == n)
// 		return (1);
// 	return (0);
// }
// "salut"

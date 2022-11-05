/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:20:05 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/05 07:14:14 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalnun(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *s1, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

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

int	ft_lst_count(t_env *env)
{
	t_env	*tmp;
	int		i;

	if (!env)
		return (0);
	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*ft_cpy(char *src, int skip)
{
	int		i;
	int		max_len;
	char	*dst;

	i = 0;
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

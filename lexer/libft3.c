/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/22 05:35:53 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;

	i = 0;
	while (src[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (0);
	dup[i] = 0;
	while (--i)
		dup[i] = src[i];
	return (dup);
}

t_cmd	*ft_get_list_last(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_list_add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*back;

	if (!*list)
	{
		*list = new;
		return ;
	}
	back = ft_get_list_last(*list);
	back->next = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/22 04:01:05 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = c;
	return (s);
}

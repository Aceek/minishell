/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/25 23:22:53 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_listclear(t_cmd **list)
{
	t_cmd	*tmp_prev;
	t_cmd	*tmp;

	if (!list)
		return ;
	tmp = *list;
	while (tmp)
	{
		tmp_prev = tmp;
		tmp = tmp_prev->next;
		free(tmp_prev);
	}
	*list = NULL;
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

static int	nb_len(int n)
{
	int		len;
	long	nl;

	len = 1;
	nl = n;
	if (nl < 0)
	{
		nl = -nl;
		len++;
	}
	while (nl >= 10)
	{
		nl /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	i;
	long			nl;

	nl = n;
	i = nb_len(nl);
	str = malloc(sizeof(char) * i + 1);
	if (str == 0)
		return (0);
	str[i] = 0;
	i--;
	if (nl < 0)
	{
		str[0] = '-';
		nl = -nl;
	}
	if (nl == 0)
		str[i] = 48;
	while (nl > 0)
	{
		str[i] = (nl % 10) + 48;
		nl = nl / 10;
	i--;
	}
	return (str);
}

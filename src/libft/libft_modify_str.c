/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_modify_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:04:36 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/28 09:13:57 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

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

int	ft_atoi(char *str, int *e)
{
	long	p;
	int		m;
	int		i;

	i = 0;
	p = 0;
	m = 1;
	if (!str)
		return (0);
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m = -m;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		p = p * 10;
		p = p + (str[i] - 48);
		i++;
	}
	*e = i;
	return (p * m);
}

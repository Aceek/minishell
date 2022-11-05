/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/05 06:19:19 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(const char *str, int c)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if ((unsigned char)c == str[i])
			return (1);
	}
	return (0);
}

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

char	*ft_strjoin2(char *s1, char c)
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

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
			i++;
	if (i == n)
		return (1);
	return (0);
}

char    *ft_strnstr(const char *s1, const char *to_find, size_t n)
{
    size_t    i;
    size_t    j;

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

char    *ft_cpy(char *src, int skip)
{
    int		i;
    int		max_len;
    char	*dst;

    i  = 0;
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

static int	is_del(char c)
{
	if (ft_isspace(c) || c == 0)
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

char	**ft_split(char *str)
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
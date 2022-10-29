/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:42:35 by ilinhard          #+#    #+#             */
/*   Updated: 2022/10/29 03:05:31 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	free_tab(char **av)
{
	int	i;

	i = 0;
	while (av && av[i] != NULL)
	{
		if (av[i])
			free(av[i]);
		i++;
	}
	if (av)
		free(av);
}

char	*ft_make_path(char *dir, char *cmd)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	path = malloc(sizeof(char) * (ft_strlen(cmd) + ft_strlen(dir) + 2));
	if (!path)
		return (NULL);
	while (dir[i])
	{
		path[i] = dir[i];
		i++;
	}
	path[i] = '/';
	i++;
	while (cmd[j])
	{
		path[i + j] = cmd[j];
		j++;
	}
	path[i + j] = '\0';
	return (path);
}

char	*ft_cpy(char *src, int skip)
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

char	*ft_get_path(char *cmd, char **env)
{
	char	*path;
	char	**all_dir;
	char	*tmp_path;
	int		i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	if (!env[i])
		return (NULL);
	tmp_path = ft_cpy(env[i], 5);
	all_dir = ft_split2(tmp_path, ':');
	i = 0;
	while (all_dir[i] != NULL)
	{
		path = ft_make_path(all_dir[i], cmd);
		if (!path)
			return (free(tmp_path), free(all_dir), NULL);
		if (access(path, F_OK) == 0)
			return (free(tmp_path), free_tab(all_dir), path);
		free (path);
		i++;
	}
	return (free(tmp_path), free_tab(all_dir), NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:42:35 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/05 07:13:08 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_make_tab_from_env(t_env *mini)
{
	int		i;
	int		len;
	char	**env;
	t_env	*tmp;

	i = 0;
	len = ft_lst_count(mini);
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (NULL);
	tmp = mini;
	while (tmp)
	{
		env[i] = ft_strdup(tmp->line);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

void	ft_exit_clean(t_env *mini, t_env *origin, t_data *data)
{
	ft_clear_data_tab(data, 1);
	ft_clear_data_tab(data, 0);
	lst_freeall(mini);
	lst_freeall(origin);
	ft_free(0, &data);
	exit(1);
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

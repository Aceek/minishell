/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:42:35 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/24 04:42:58 by pbeheyt          ###   ########.fr       */
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


void	ft_exit_clean(t_env *mini, t_cmd *cmd)
{
	ft_clear_cmd_list(cmd);
	(void)cmd;
	lst_freeall(mini);
	rl_clear_history();
	exit(1);
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

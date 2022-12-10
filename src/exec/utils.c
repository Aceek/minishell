/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:42:35 by ilinhard          #+#    #+#             */
/*   Updated: 2022/12/10 03:23:43 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_and_reset_exec(t_cmd *cmd, int error)
{
	if (error)
		g_exit = 1;
	dup2(cmd->cpy_out, STDOUT_FILENO);
	dup2(cmd->cpy_in, STDIN_FILENO);
	close(cmd->cpy_in);
	close(cmd->cpy_out);
	while (wait(NULL) > 0)
		;
	ft_clear_cmd_list(cmd);
}

void	ft_exec_err(const char *str, char *var)
{
	if (str)
		write(2, str, ft_strlen(str));
	if (var)
		write(2, var, ft_strlen(var));
}

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
	all_dir = ft_split2(tmp_path, ":");
	i = 0;
	while (all_dir[i] != NULL)
	{
		path = ft_make_path(all_dir[i], cmd);
		if (!path)
			return (free(tmp_path), free(all_dir), NULL);
		if (access(path, F_OK) == 0)
			return (free(tmp_path), ft_clear_tab(all_dir), path);
		free (path);
		i++;
	}
	return (free(tmp_path), ft_clear_tab(all_dir), NULL);
}

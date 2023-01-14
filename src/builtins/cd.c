/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:29:10 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/14 02:19:47 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env_path(char *env_path, t_env *mini)
{
	char	*path;
	t_env	*tmp;
	int		len;

	tmp = mini;
	len = ft_strlen(env_path);
	while (tmp)
	{
		if (ft_strncmp(tmp->line, env_path, len) == 0)
		{
			path = ft_cpy(tmp->line, len);
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_update_pwd(t_env *mini, char *join, int mod)
{
	char	buff[2048];
	char	*pwd;

	if (getcwd(buff, 2048) == NULL)
		return (NULL);
	pwd = ft_strjoin(join, buff);
	if (mod)
	{
		if (!ft_is_in_env(mini, pwd))
			ft_add_list_env(mini, pwd);
		free(pwd);
		return (NULL);
	}
	else
		return (pwd);
}

int	ft_go_path(int location, t_env *mini)
{
	char	*path;
	char	*old_pwd;

	path = NULL;
	if (!location)
		path = ft_get_env_path("HOME=", mini);
	else if (location == 1)
		path = ft_get_env_path("OLDPWD=", mini);
	if (!path)
		return (write(2, "cd : OLDPWD or HOME not set\n", 28), -1);
	old_pwd = ft_update_pwd(mini, "OLDPWD=", 0);
	if (chdir(path) < 0)
	{
		g_exit = 1;
		write(2, "cd: no such file or directory\n", 30);
	}
	else if (!ft_is_in_env(mini, old_pwd))
		ft_add_list_env(mini, old_pwd);
	ft_update_pwd(mini, "PWD=", 1);
	return (free(path), free(old_pwd), 0);
}

char	*ft_handle_tild(char *str, t_env *mini)
{
	char	*tmp;
	char	*path_home;

	path_home = ft_get_env_path("HOME=", mini);
	if (!path_home)
		return (NULL);
	tmp = ft_cpy(str, 1);
	if (!tmp)
	{
		free(path_home);
		return (NULL);
	}
	free(str);
	str = ft_strjoin(path_home, tmp);
	free(path_home);
	free(tmp);
	return (str);
}

int	ft_cd_builtind(t_cmd *cmd, t_env *mini)
{
	char	*old_pwd;

	if (!cmd->tab[1] || (cmd->tab[1][0] == '~'
		&& cmd->tab[1][1] == '\0'))
		ft_go_path(0, mini);
	else if (cmd->tab[1] && !ft_strncmp(cmd->tab[1], "-", 1))
		ft_go_path(1, mini);
	else if (cmd->tab[1])
	{
		if (cmd->tab[1][0] == '~')
			cmd->tab[1] = ft_handle_tild(cmd->tab[1], mini);
		old_pwd = ft_update_pwd(mini, "OLDPWD=", 0);
		if (chdir(cmd->tab[1]) < 0)
		{
			g_exit = 1;
			write(2, "cd: no such file or directory\n", 30);
		}
		else if (!ft_is_in_env(mini, old_pwd))
			ft_add_list_env(mini, old_pwd);
		ft_update_pwd(mini, "PWD=", 1);
		free(old_pwd);
	}
	return (g_exit);
}

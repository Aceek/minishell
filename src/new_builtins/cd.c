/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:29:10 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/18 06:26:46 by ilinhard         ###   ########.fr       */
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

void	ft_update_pwd(t_env *mini, char *join)
{
	char	buff[2048];
	char	*pwd;

	if (getcwd(buff, 2048) == NULL)
		return ;
	pwd = ft_strjoin(join, buff);
	if (!ft_is_in_env(mini, pwd))
		ft_add_list_env(mini, pwd);
	free(pwd);
}

int	ft_go_path(int location, t_env *mini)
{
	char	*path;

	if (!location)
	{
		path = ft_get_env_path("HOME=", mini);
		if (!path)
			return (printf("cd : HOME not set\n"), -1);
	}
	else if (location == 1)
	{
		path = ft_get_env_path("OLDPWD=", mini);
		if (!path)
			return (printf("cd : OLDPWD not set\n"), -1);
	}
	ft_update_pwd(mini, "OLDPWD=");
	chdir(path);
	ft_update_pwd(mini, "PWD=");
	free(path);
	return (0);
}

void	ft_cd_builtind(t_data *data, t_env *mini)
{
	if (!data->new_args[1] || (data->new_args[1][0] == '~'
		&& data->new_args[1][1] == '\0'))
		ft_go_path(0, mini);
	else if (data->new_args[1] && !ft_strncmp(data->new_args[1], "-", 1))
		ft_go_path(1, mini);
	else if (data->new_args[1])
	{
		ft_update_pwd(mini, "OLDPWD=");
		if (chdir(data->new_args[1]) < 0)
			printf("Path not found\n");
		ft_update_pwd(mini, "PWD=");
	}
}

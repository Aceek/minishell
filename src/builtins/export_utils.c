/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 07:16:10 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/24 05:47:55 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtin(t_cmd *cmd, t_env *mini)
{
	if (cmd->builtin == EXPORT)
		ft_export_builtin(cmd, mini);
	else if (cmd->builtin == ECH)
		ft_echo_builtin(cmd);
	else if (cmd->builtin == PWD)
		ft_pwd_builtin();
	else if (cmd->builtin == UNSET)
		ft_unset_builtin(cmd, mini);
	else if (cmd->builtin == ENV)
		ft_print_env(mini);
	else if (cmd->builtin == CD)
		ft_cd_builtind(cmd, mini);
	else if (cmd->builtin == EXIT)
		ft_exit_clean(mini, cmd);
	return ;
}

int	ft_is_valid_env(char *args)
{
	int		i;

	i = 0;
	if (ft_isdigit(args[0]) || args[0] == '=' || args[0] == '\0')
		return (-1);
	while (args && args[i] && args[i] != '=')
	{
		if (ft_isalnun_tmp(args[i]) == 0)
			return (-1);
		i++;
	}
	if (args[i] != '=')
		return (2);
	return (1);
}

int	ft_is_in_env(t_env *mini, char *args)
{
	t_env	*tmp;
	char	*tmp_args;

	tmp = mini;
	while (tmp)
	{
		tmp_args = ft_cpy_env_name(args);
		if (ft_strncmp(tmp->line, tmp_args, ft_strlen(tmp_args)) == 0)
		{
			free(tmp->line);
			tmp->line = ft_strdup(args);
			free(tmp_args);
			return (1);
		}
		free(tmp_args);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*ft_cpy_env(t_env *mini)
{
	t_env	*tmp;
	t_env	*cpy;

	tmp = mini;
	cpy = malloc(sizeof(t_env));
	if (!cpy)
		return (NULL);
	cpy->line = NULL;
	cpy->next = NULL;
	while (tmp)
	{
		lst_addback(cpy, tmp->line);
		tmp = tmp->next;
	}
	return (cpy);
}

void	ft_print_export_env(t_env *mini)
{
	t_env	*tmp;
	int		i;
	int		egal;

	tmp = mini;
	while (tmp)
	{
		egal = 1;
		i = -1;
		write(1, "declare -x ", 11);
		while (tmp->line && tmp->line[++i])
		{
			write(1, &tmp->line[i], 1);
			if (egal == 1 && tmp->line[i] == '=')
			{
				egal += 1;
				write(1, "\"", 1);
			}
			if (egal > 1 && tmp->line[i + 1] == '\0')
				write(1, "\"", 1);
		}
		write(1, "\n", 2);
		tmp = tmp->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 07:16:10 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/18 04:30:49 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtin(t_data *data, t_env *mini, t_env *origin)
{
	if (data->code == EXPORT)
		ft_export_builtin(data, mini, origin);
	else if (data->code == ECH)
		ft_echo_builtin(data);
	else if (data->code == PWD)
		ft_pwd_builtin();
	else if (data->code == UNSET)
		ft_unset_builtin(data, mini);
	else if (data->code == ENV)
		ft_print_env(mini);
	else if (data->code == CD)
		ft_cd_builtind(data, mini);
	else if (data->code == EXIT)
		exit(1);
	return ;
}

int	ft_is_valid_env(char *args)
{
	int		i;
	char	*cpy;

	i = 0;
	if (ft_isdigit(args[0]) || args[0] == '=')
		return (-1);
	while (args && args[i] && args[i] != '=')
	{
		if (ft_isalnun(args[i]) == 0)
			return (-1);
		i++;
	}
	if (args[i] != '=')
	{
		cpy = ft_strdup(args);
		free(args);
		args = ft_strjoin(cpy, "=");
		free(cpy);
		return (2);
	}
	return (1);
}

int	ft_export_error(int error, char *args)
{
	if (error == -1)
		printf("export : not an identifier : %s\n", args);
	return (error);
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

void	ft_print_env(t_env *origin)
{
	t_env	*tmp;

	tmp = origin;
	while (tmp)
	{
		if (tmp->line)
			printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}

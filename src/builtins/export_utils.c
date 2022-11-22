/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 07:16:10 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/20 01:46:17 by ilinhard         ###   ########.fr       */
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
		ft_print_env(mini, 0);
	else if (data->code == CD)
		ft_cd_builtind(data, mini);
	else if (data->code == EXIT)
		ft_exit_clean(mini, origin, data);
	return ;
}

int	ft_is_valid_env(char *args)
{
	int		i;
	// char	*cpy;

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
		// cpy = ft_strdup(args);
		// free(args);
		// args = ft_strjoin(cpy, "=");
		// free(cpy);
		return (2);
	}
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

void	ft_print_env(t_env *origin, int mod)
{
	t_env	*tmp;

	tmp = origin;
	while (tmp)
	{
		if (tmp->line)
		{
			if (mod)
				printf("declare -x ");
			printf("%s\n", tmp->line);
		}
		tmp = tmp->next;
	}
}

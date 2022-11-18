/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 07:12:28 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/18 00:49:06 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_print_env(t_env *origin)
{
	t_env	*cpy;
	char	*tmp;
	int		len;

	if (!origin || !origin->line)
	{
		printf("error export env\n");
		return ;
	}
	cpy = origin;
	while (cpy && cpy->next)
	{
		len = ft_strlen(cpy->line) + ft_strlen(cpy->next->line);
		if (ft_strncmp(cpy->line, cpy->next->line, len) > 0)
		{
			tmp = cpy->line;
			cpy->line = cpy->next->line;
			cpy->next->line = tmp;
			cpy = origin;
		}
		else
			cpy = cpy->next;
	}
	ft_print_env(origin);
}

char	*ft_cpy_env_name(char *args)
{
	int		i;
	char	*new;

	i = 0;
	while (args && args[i] && args[i] != '=')
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (args && args[i] && args[i] != '=')
	{
		new[i] = args[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	ft_add_list_env(t_env *mini, char *args)
{
	t_env	*tmp;
	t_env	*new;

	if (mini && !mini->line)
	{
		mini->line = ft_strdup(args);
		return ;
	}
	else if (!mini)
	{
		printf("Error env does not exist\n");
		return ;
	}
	tmp = mini;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->next = NULL;
	new->line = ft_strdup(args);
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_add_args_env(t_data *data, t_env *mini, t_env *origin)
{
	int	env;
	int	error;
	int	i;

	(void)origin;
	env = 0;
	i = 1;
	while (data->new_args && data->new_args[i])
	{
		error = ft_is_valid_env(data->new_args[i]);
		if (error < 0)
			ft_export_error(error, data->new_args[i]);
		else if (error > 0)
			env = ft_is_in_env(mini, data->new_args[i]);
		if (error > 0 && env == 0)
			ft_add_list_env(mini, data->new_args[i]);
		i++;
	}
}

void	ft_export_builtin(t_data *data, t_env *mini, t_env *origin)
{
	if (!data->new_args[1] && mini)
	{
		ft_sort_print_env(mini);
		return ;
	}
	else
		ft_add_args_env(data, mini, origin);
	return ;
}

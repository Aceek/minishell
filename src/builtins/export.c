/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 07:12:28 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/20 01:40:51 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_print_env(t_env *mini)
{
	t_env	*cpy;
	char	*tmp;
	int		len;

	if (!mini || !mini->line)
	{
		printf("error export env\n");
		return ;
	}
	cpy = mini;
	while (cpy && cpy->next)
	{
		len = ft_strlen(cpy->line) + ft_strlen(cpy->next->line);
		if (ft_strncmp(cpy->line, cpy->next->line, len) > 0)
		{
			tmp = cpy->line;
			cpy->line = cpy->next->line;
			cpy->next->line = tmp;
			cpy = mini;
		}
		else
			cpy = cpy->next;
	}
	ft_print_env(mini, 1);
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
			printf("export : not an identifier : %s\n", data->new_args[i]);
		else if (error > 0)
			env = ft_is_in_env(mini, data->new_args[i]);
		if (error > 0 && env == 0)
			ft_add_list_env(mini, data->new_args[i]);
		i++;
	}
}

void	ft_export_builtin(t_data *data, t_env *mini, t_env *origin)
{
	t_env	*tmp_cpy;

	tmp_cpy = NULL;
	if (!data->new_args[1] && mini)
	{
		tmp_cpy = ft_cpy_env(mini);
		ft_sort_print_env(tmp_cpy);
		lst_freeall(tmp_cpy);
	}
	else
		ft_add_args_env(data, mini, origin);
	return ;
}

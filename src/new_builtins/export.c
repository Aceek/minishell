/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 07:12:28 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/05 06:11:05 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_env *origin)
{
	t_env *tmp;

	tmp = origin;
	while (tmp)
	{
		if (tmp->line)
			printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}

void	ft_sort_print_env(t_env *origin)
{
	t_env	*cpy;
	char	*tmp;
	int		len;

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

int	ft_is_valid_env(char *args)
{
	int	i;

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
		return (2);
	return (1);
}

int	ft_export_error(int error, char *args)
{
	if (error == -1)
		printf("export : not an identifier : %s\n", args);
	return (error);
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

int	ft_is_in_env(t_env *mini, char *args)
{
	t_env *tmp;
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

void	ft_add_list_env(t_env *mini, char *args)
{
	t_env *tmp;
	t_env *new;

	tmp = mini;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->next = NULL;
	new->line = ft_strdup(args);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void ft_add_args_env(t_data *data, t_env *mini, t_env *origin)
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
	if (!data->new_args[1])
	{
		ft_sort_print_env(mini);
		return ;
	}
	else
		ft_add_args_env(data, mini, origin);
	return ;
}

void	ft_builtin(t_data *data, t_env *mini, t_env *origin)
{
	if (data->code == EXPORT)
		ft_export_builtin(data, mini, origin);
	return ;
		
}

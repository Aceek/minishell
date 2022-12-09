/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 07:12:28 by ilinhard          #+#    #+#             */
/*   Updated: 2022/12/09 23:49:21 by ilinhard         ###   ########.fr       */
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
		write(2, "error export env\n", 17);
		g_exit = 1;
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
	ft_print_export_env(mini);
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
		return ;
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

void	ft_add_args_env(t_cmd *cmd, t_env *mini)
{
	int	env;
	int	error;
	int	i;

	env = 0;
	i = 1;
	while (cmd->tab && cmd->tab[i])
	{
		g_exit = 0;
		error = ft_is_valid_env(cmd->tab[i]);
		if (error < 0)
		{
			g_exit = 1;
			write(2, cmd->tab[i], ft_strlen(cmd->tab[i]));
			write(2, " : export : not an identifier\n", 30);
		}
		else if (error > 0)
			env = ft_is_in_env(mini, cmd->tab[i]);
		if (error > 0 && env == 0)
			ft_add_list_env(mini, cmd->tab[i]);
		i++;
	}
}

int	ft_export_builtin(t_cmd *cmd, t_env *mini)
{
	// t_env	*tmp_cpy;

	// tmp_cpy = NULL;
	if (!cmd->tab[1] && mini)
	{
		return (0);
		// tmp_cpy = ft_cpy_env(mini);
		// ft_sort_print_env(tmp_cpy);
		// lst_freeall(tmp_cpy);
	}
	else
		ft_add_args_env(cmd, mini);
	return (g_exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/23 05:02:17 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}

int	ft_strchr(const char *str, int c)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if ((unsigned char)c == str[i])
			return (1);
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// -----------------------------------------------------------------------------------------

int	lst_addback(t_env *mini_env, char *env)
{
	t_env	*temp;
	t_env	*env_clone;

	env_clone = mini_env;
	if (!env_clone->line)
		return (env_clone->line = ft_strdup(env), 1);
	temp = malloc(sizeof(t_env));
	if (!temp)
		return (0);
	temp->line = ft_strdup(env);
	temp->next = NULL;
	if (!temp->line)
		return (free(temp), 0);
	while (env_clone->next)
		env_clone = env_clone->next;
	env_clone->next = temp;
	return (1);
}

int	ft_atoi(char *str, int *e)
{
	long	p;
	int		m;
	int		i;

	i = 0;
	p = 0;
	m = 1;
	if (!str)
		return (0);
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m = -m;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		p = p * 10;
		p = p + (str[i] - 48);
		i++;
	}
	*e = i;
	return (p * m);
}

void	lst_freeall(t_env *mini_env)
{
	t_env	*temp;

	while (mini_env)
	{
		temp = mini_env;
		mini_env = mini_env->next;
		if (temp->line)
		{
			free(temp->line);
			temp->line = NULL;
		}
		free(temp);
	}
}

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalnun_tmp(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	ft_lst_count(t_env *env)
{
	t_env	*tmp;
	int		i;

	if (!env)
		return (0);
	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}



// -------------------------------------------------------

void	ft_clear_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	ft_clear_fd(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
		close (cmd->fd_in);
	if (cmd->fd_out > 1)
		close (cmd->fd_out);
}

void	ft_clear_data_tab(t_cmd *cmd, int booll)
{
	t_cmd *tmp;

	if (cmd)
	{
		tmp = cmd;
		while (tmp)
		{
			if (booll && tmp->tab)
				ft_clear_tab(tmp->tab);
			else if (!booll && tmp->tab)
				ft_clear_fd(tmp);
			tmp = tmp->next;
		}
	}
}
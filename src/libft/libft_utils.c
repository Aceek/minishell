/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:11:57 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/27 06:27:01 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_strdup(char *s)
{
	int		i;
	int		y;
	char	*dest;

	if (!s)
		return (0);
	i = 0;
	y = 0;
	while (s[y] != '\0')
		y++;
	dest = malloc(sizeof(char) * (y + 1));
	if (!dest)
		return (0);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	nb_len(int n)
{
	int		len;
	long	nl;

	len = 1;
	nl = n;
	if (nl < 0)
	{
		nl = -nl;
		len++;
	}
	while (nl >= 10)
	{
		nl /= 10;
		len++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:24:41 by mgalt             #+#    #+#             */
/*   Updated: 2020/07/16 20:09:00 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
}

int		len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

double	ft_strtodbl(char *s)
{
	char		**tab;
	double		n;
	int			i;
	double		tmp;
	int			len;
	int			dot;

	n = 0.0;
	i = 0;
	tmp = 0;
	dot = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '.')
			dot++;
		i++;
	}
	if (!dot)
		return ((double)ft_atoi(s));
	tab = ft_strsplit(s, '.');
	n = (double)ft_atoi(tab[0]);
	tmp = (double)ft_atoi(tab[1]);
	len = ft_strlen(tab[1]);
	while (len > 0)
	{
		tmp /= 10;
		len--;
	}
	n += tmp;
	free_tab(tab);
	return (n);
}

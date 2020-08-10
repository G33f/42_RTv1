/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:38:51 by mgalt             #+#    #+#             */
/*   Updated: 2020/08/06 20:59:26 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		camera(t_data *p, char **tab)
{
	char	**tab1;

	tab1 = NULL;
	tab1 = ft_strsplit(tab[1], ',');
	if (len_tab(tab1) < 9)
	{
		free_tab(tab1);
		return (-1);
	}
	p->camera.canv_h = ft_atoi(tab1[0]);
	p->camera.canv_w = ft_atoi(tab1[1]);
	p->camera.canv_d = ft_atoi(tab1[2]);
	p->camera.x = ft_strtodbl(tab1[3]);
	p->camera.y = ft_strtodbl(tab1[4]);
	p->camera.z = ft_strtodbl(tab1[5]);
	p->camera.rot_x = ft_strtodbl(tab1[6]);
	p->camera.rot_y = ft_strtodbl(tab1[7]);
	p->camera.rot_z = ft_strtodbl(tab1[8]);
	free_tab(tab1);
	return (0);
}

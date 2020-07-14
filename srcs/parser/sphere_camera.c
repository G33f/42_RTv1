/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:38:51 by mgalt             #+#    #+#             */
/*   Updated: 2020/07/14 16:40:37 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_orb	*new_orb(t_orb new)
{
	t_orb	*orb;

	orb = (t_orb*)malloc(sizeof(t_orb));
	orb->x = new.x;
	orb->y = new.y;
	orb->z = new.z;
	orb->r = new.r;
	orb->specular = new.specular;
	orb->color = new.color;
	orb->type = new.type;
	orb->next = NULL;
	return (orb);
}

int		sphere_init(t_data *p, int *n, char *line)
{
	t_orb	o1;
    t_orb   *o2;
	char	**tab1;
	int		tab_len;
	int		i;

	i = 0;
	*n += 1;
	p->obj[*n].type = SPHERE;
	tab1 = NULL;
	tab1 = ft_strsplit(line, ',');
	tab_len = len_tab(tab1);
	if (tab_len < 6)
	{
		free_tab(tab1);
		return (-1);
	}
	o1 = orb_init(ft_atoi(tab1[0]), ft_atoi(tab1[1]), ft_atoi(tab1[2]),
	ft_atoi(tab1[3]), tab1[4], ft_strtodbl(tab1[5]), SPHERE);
	//printf("o1: %d %d %d %f %d %f %d\n", o1.x, o1.y, o1.z, o1.r, o1.color, o1.specular, o1.type);
    o2 = new_orb(o1);
	ft_lstadd(&p->figur, ft_lstnew(o2, sizeof(t_orb)));
    free(o2);
	free_tab(tab1);
	return (0);
}

int		camera(t_data *p, char **tab)
{
	char	**tab1;

	tab1 = NULL;
	tab1 = ft_strsplit(tab[1], ',');
	if (len_tab(tab1) < 6)
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
	free_tab(tab1);
	return (0);
}

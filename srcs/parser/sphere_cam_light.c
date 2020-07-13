/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_cam_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:16:20 by mgalt             #+#    #+#             */
/*   Updated: 2020/07/13 16:20:21 by mgalt            ###   ########.fr       */
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
	printf("new orb: %d %d %d %f %f %d %d\n", orb->x, orb->y, orb->z, orb->r, orb->specular, orb->color, orb->type);
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
	strtod(tab1[3], NULL), strtod(tab1[4], NULL), ft_atoi(tab1[5]), SPHERE);
    o2 = new_orb(o1);
	ft_lstadd(&p->figur, ft_lstnew(o2, sizeof(t_orb)));
    free(o2);
	free_tab(tab1);
	return (0);
}

int		set_light(t_data *p, char **tab)
{
	char	**tab1;

	tab1 = ft_strsplit(tab[2], ',');
	if (len_tab(tab1) < 4)
	{
		free_tab(tab1);
		return (-1);
	}
	if (ft_strequ(tab[0], "light") && ft_strequ(tab[1], "point"))
	{
		p->l_p = new_vec(ft_atoi(tab1[0]), ft_atoi(tab1[1]), ft_atoi(tab1[2]));
		p->intens_p = strtod(tab1[3], NULL);
	}
	if (ft_strequ(tab[0], "light") && ft_strequ(tab[1], "direction"))
	{
		p->l_d = new_vec(ft_atoi(tab1[0]), ft_atoi(tab1[1]), ft_atoi(tab1[2]));
		//p->l_d = rev_vec(p->l_d);
		p->intens_d = strtod(tab1[3], NULL);
	}
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
	p->camera.x = strtod(tab1[3], NULL);
	p->camera.y = strtod(tab1[4], NULL);
	p->camera.z = strtod(tab1[5], NULL);
	free_tab(tab1);
	return (0);
}

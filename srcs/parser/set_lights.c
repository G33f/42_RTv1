/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:39:03 by mgalt             #+#    #+#             */
/*   Updated: 2020/08/11 17:09:11 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light	*new_light(t_light l)
{
	t_light	*light;

	light = (t_light*)malloc(sizeof(t_light));
	light->x = l.x;
	light->y = l.y;
	light->z = l.z;
	light->intens = l.intens;
	return (light);
}

t_light	light_init(double x, double y, double z, double intens)
{
	t_light	light;

	light.x = x;
	light.y = y;
	light.z = z;
	light.intens = intens;
	return (light);
}

void	lights_init(t_data *p, char **s)
{
	t_light		l1;
	t_light		*l2;

	l1 = light_init(ft_strtodbl(s[0]), ft_strtodbl(s[1]),
			ft_strtodbl(s[2]), ft_strtodbl(s[3]));
	l2 = new_light(l1);
	ft_lstadd(&p->light, ft_lstnew(l2, sizeof(t_light)));
	free(l2);
}

void	ambience(t_data *p, char *s)
{
	p->ambient = ft_strtodbl(s);
	if (p->ambient > 1)
		p->ambient = 1;
}

int		set_light(t_data *p, char **tab)
{
	char	**tab1;

	tab1 = ft_strsplit(tab[2], ',');
	if (len_tab(tab1) < 4)
	{
		free_tab(tab1);
		error_output(PARAMETERS);
		exit(0);
	}
	if (ft_strequ(tab[0], "light") && ft_strequ(tab[1], "point"))
		lights_init(p, tab1);
	free_tab(tab1);
	return (0);
}

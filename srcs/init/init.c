/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:54:36 by wpoudre           #+#    #+#             */
/*   Updated: 2020/08/22 19:10:10 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	obj_clon(const t_list *o)
{
	t_obj	obj;

	obj.c = ((t_obj*)o->content)->c;
	obj.v = ((t_obj*)o->content)->v;
	obj.a = ((t_obj*)o->content)->a;
	obj.r = ((t_obj*)o->content)->r;
	obj.specular = ((t_obj*)o->content)->specular;
	obj.color = ((t_obj*)o->content)->color;
	obj.type = ((t_obj*)o->content)->type;
	return (obj);
}

t_obj	obj_init2(t_obj obj, double specular, char *color, int type)
{
	obj.specular = specular;
	if (ft_strequ(color, "red"))
		obj.color = RED;
	else if (ft_strequ(color, "green"))
		obj.color = GREEN;
	else if (ft_strequ(color, "blue"))
		obj.color = BLUE;
	else if (ft_strequ(color, "yellow"))
		obj.color = YELLOW;
	else if (ft_strequ(color, "aqua"))
		obj.color = AQUA;
	else if (ft_strequ(color, "gray"))
		obj.color = GRAY;
	else if (ft_strequ(color, "grey"))
		obj.color = GREY;
	else if (ft_strequ(color, "grey1"))
		obj.color = GREY1;
	else
		obj.color = 249710846;
	obj.type = type;
	return (obj);
}

t_obj	obj_init1(t_vector c, t_vector v, double a, double r)
{
	t_obj	obj;

	obj.c = c;
	obj.v = v;
	while (a > 360.0)
		a -= 360.0;
	while (a < 0.0)
		a += 360.0;
	obj.a = (a * PI) / 180.0;
	obj.r = r;
	return (obj);
}

t_obj	*new_obj(t_obj new)
{
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->c = new.c;
	obj->v = new.v;
	obj->a = new.a;
	obj->r = new.r;
	obj->specular = new.specular;
	obj->color = new.color;
	obj->type = new.type;
	return (obj);
}

int		init(t_data *p)
{
	init_mlx(p);
	return (0);
}

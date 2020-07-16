/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:54:36 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/03 15:54:41 by wpoudre          ###   ########.fr       */
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
	return(obj);
}

int camera_init(t_data *p)
{
	p->camera.canv_h = 960;
	p->camera.canv_w = 960;
	p->camera.canv_d = 960;
	p->camera.x = 0;
	p->camera.y = 0;
	p->camera.z = 0;
	return(0);
}

int	init(t_data *p)
{
	camera_init(p);
	init_mlx(p);
	return(0);
}
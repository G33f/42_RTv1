/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figur_and_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:06:48 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/10 19:06:51 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light	light_init(double x, double y, double z, double intens)
{
	t_light	light;

	light.x = x;
	light.y = y;
	light.z = z;
	light.intens = intens;
	return (light);
}

t_obj	obj_init(t_vector c, t_vector v, double a, double r, double specular, int color, int type)
{
	t_obj	obj;

	obj.c = c;
	obj.v = v;
	obj.a = a;
	obj.r = r;
	obj.specular = specular;
	obj.color = color;
	obj.type = type;
	return (obj);
}

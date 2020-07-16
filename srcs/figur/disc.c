/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:46:17 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/16 23:34:38 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	disk_sphere(t_vector d, t_vector oc, t_obj *figur)
{
	return (pow((2 * vec_dot(oc, d)), 2) - (4 * vec_dot(d, d) *
	(vec_dot(oc, oc) - pow(figur->r, 2))));
}

double	disk_cone(t_vector d, t_vector oc, t_obj *figur)
{
	double	a;
	double	b;
	double	c;
	double	f;

	figur->v = vec_divis_cst(figur->v, vec_length(figur->v));
	f = tan(figur->a);
	d = vec_divis_cst(d, vec_length(d));
	a = (pow(vec_dot(d, figur->v), 2) - pow(cos(f), 2));
	b = (2 * (vec_dot(d, figur->v) * vec_dot(oc, figur->v) - vec_dot(d, oc) * pow(cos(f), 2)));
	c = (pow(vec_dot(oc, figur->v), 2) - vec_dot(oc, oc) * pow(cos(f), 2));
	return (pow(b, 2) - (4 * a * c));
}

double	disk_cyl(t_vector d, t_vector oc, t_obj *figur)
{
	double	a;
	double	b;
	double	c;
	//double	f;

	figur->v = vec_divis_cst(figur->v, vec_length(figur->v));
	//f = tan(figur->a);
	//d = vec_divis_cst(d, vec_length(d));
	//a = (pow(vec_dot(d, figur->v), 2) - pow(cos(f), 2));
	a = vec_dot(d, d) - pow(vec_dot(d, figur->v), 2);
	b = (-2 * (vec_dot(d, figur->v) * vec_dot(oc, figur->v) + 2 * vec_dot(d, oc)));
	c = (-1 * pow(vec_dot(oc, figur->v), 2) + vec_dot(oc, oc) - pow(figur->r, 2));
	return (pow(b, 2) - (4 * a * c));
}

/*double	disk_pl(t_vector d, t_vector oc, t_obj *figur)
{

}*/

double	f_disk(t_vector d, t_vector oc, t_obj *figur)
{
	if (figur->type == SPHERE)
		return (disk_sphere(d, oc, figur));
	if (figur->type == CONE)
		return (disk_cone(d, oc, figur));
	if (figur->type == CYLINDER)
		return (disk_cyl(d, oc, figur));
	//if (figur->type == PLANE)
		//return (disk_pl(d, oc, figur));
	return (0.0);
}

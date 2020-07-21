/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:46:17 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/17 13:00:12 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	*disk_sphere(t_vector d, t_vector oc, t_obj *figur, double *t)
{
	double	disk;

	disk = pow((2 * vec_dot(oc, d)), 2) - (4 * vec_dot(d, d) *
			(vec_dot(oc, oc) - pow(figur->r, 2)));
	t[0] = ((-2 * vec_dot(oc, d)) + sqrt(disk)) / (2 * vec_dot(d, d));
	t[1] = ((-2 * vec_dot(oc, d)) - sqrt(disk)) / (2 * vec_dot(d, d));
	t[0] = min(t[0], t[1]);
	return (t);
}

double	*disk_cone(t_vector d, t_vector oc, t_obj *figur, double *t)
{
	double	a;
	double	b;
	double	c;
	double	disk;
	t_disk	r;

	r.v_min_vdotva = vec_diff(d, vec_mult_cst(figur->v, vec_dot(figur->v, d)));
	r.v_min_vdotva_sqr = vec_dot(r.v_min_vdotva, r.v_min_vdotva);
	r.delta_p = vec_diff(oc, vec_mult_cst(figur->v, vec_dot(figur->v, oc)));
	r.delta_p_sqr = vec_dot(r.delta_p, r.delta_p);
	r.cos_a_sqr = pow(cos(figur->a), 2);
	r.sin_a_sqr = pow(sin(figur->a), 2);
	r.dot_oc_v = vec_dot(oc, figur->v);

	a = r.cos_a_sqr * r.v_min_vdotva_sqr - (r.sin_a_sqr * pow(vec_dot(d, figur->v), 2));
	b = 2 * r.cos_a_sqr * (vec_dot(r.v_min_vdotva, r.delta_p)) - (2 * r.sin_a_sqr * vec_dot(d, figur->v) * r.dot_oc_v);
	c = r.cos_a_sqr * r.delta_p_sqr - r.sin_a_sqr * pow(r.dot_oc_v, 2);

	disk = pow(b, 2) - (4 * a * c);
	t[0] = ((-b) + sqrt(disk)) / (2 * a);
	t[1] = ((-b) - sqrt(disk)) / (2 * a);
	t[0] = min(t[0], t[1]);
	return (t);
}

double	*disk_cyl(t_vector d, t_vector oc, t_obj *figur, double *t)
{
	double	a;
	double	b;
	double	c;
	double	disk;

	a = vec_dot(vec_diff(d, vec_mult_cst(figur->v, vec_dot(figur->v, d))), vec_diff(d, vec_mult_cst(figur->v, vec_dot(figur->v, d))));
	b =	2 * vec_dot(vec_diff(d, vec_mult_cst(figur->v, vec_dot(figur->v, d))), vec_diff(oc, vec_mult_cst(figur->v, vec_dot(figur->v, oc))));
	c = vec_dot(vec_diff(oc, vec_mult_cst(figur->v, vec_dot(figur->v, oc))), vec_diff(oc, vec_mult_cst(figur->v, vec_dot(figur->v, oc)))) - pow(figur->r, 2);
	disk = pow(b, 2) - (4 * a * c);
	t[0] = ((-b) + sqrt(disk)) / (2 * a);
	t[1] = ((-b) - sqrt(disk)) / (2 * a);
	t[0] = min(t[0], t[1]);
	return (t);
}

double	*f_disk(t_vector d, t_vector oc, t_obj *figur, double *t)
{
	if (figur->type == SPHERE)
		return (disk_sphere(d, oc, figur, t));
	if (figur->type == CONE)
		return (disk_cone(d, oc, figur, t));
	if (figur->type == CYLINDER)
		return (disk_cyl(d, oc, figur, t));
	//if (figur->type == PLANE)
		//return (disk_pl(d, oc, figur));
	return (t);
}

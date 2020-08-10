/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 21:44:54 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/17 12:51:33 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	norm_sphere(t_obj *fig, t_vector p)
{
	t_vector	n;

	n = vec_diff(p, fig->c);
	n = vec_divis_cst(n, vec_length(n));
	return (n);
}

t_vector	norm_cone(double t, t_3_vec buf, t_obj *fig)
{
	t_vector	n;
	double		k;
	t_vector	p;
	t_vector	d;
	t_vector	oc;

	p = buf.p;
	d = buf.n;
	oc = buf.v;
	k = tan(fig->a);
	t = vec_dot(d, fig->v) * t + vec_dot(oc, fig->v);
	n = vec_diff(vec_diff(p, fig->c), vec_mult_cst(fig->v, (1 + k * k) * t));
	n = vec_divis_cst(n, vec_length(n));
	return (n);
}

t_vector	norm_cyl(double t, t_3_vec buf, t_obj *fig)
{
	double		m;
	t_vector	n;
	t_vector	p;
	t_vector	d;
	t_vector	oc;

	p = buf.p;
	d = buf.n;
	oc = buf.v;
	fig->v = vec_divis_cst(fig->v, vec_length(fig->v));
	m = vec_dot(d, fig->v) * t + vec_dot(oc, fig->v);
	n = vec_diff(vec_diff(p, fig->c), vec_mult_cst(fig->v, m));
	n = vec_divis_cst(n, vec_length(n));
	return (n);
}

t_vector	normals(t_data *q, t_obj *fig, t_3_vec buf, double t)
{
	buf.v = vec_diff(new_vec(q->camera.x, q->camera.y, q->camera.z), fig->c);
	if (fig->type == SPHERE)
		return (norm_sphere(fig, buf.p));
	if (fig->type == CONE)
		return (norm_cone(t, buf, fig));
	if (fig->type == CYLINDER)
		return (norm_cyl(t, buf, fig));
	if (fig->type == PLANE)
	{
		if (vec_dot(buf.n, fig->v) > 0)
			return (rev_vec(fig->v));
		else
			return (fig->v);
	}
	return ((t_vector){0, 0, 0});
}

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

t_vector	norm_cone(t_vector oc, double t, t_vector d, t_vector p, t_obj *fig)
{
	double		m;
	t_vector	n;
	double		k;

	k = tan(fig->a);
	m = vec_dot(d, fig->v) * t + vec_dot(oc, fig->v);
	n = vec_diff(vec_diff(p, fig->c), vec_mult_cst(fig->v, (1 + k * k) * m));
	n = vec_divis_cst(n, vec_length(n));
	return (n);
}

t_vector	norm_cyl(t_vector oc, double t, t_vector d, t_vector p, t_obj *fig)
{
	double		m;
	t_vector	n;

	fig->v = vec_divis_cst(fig->v, vec_length(fig->v));
	m = vec_dot(d, fig->v) * t + vec_dot(oc, fig->v);
	n = vec_diff(vec_diff(p, fig->c), vec_mult_cst(fig->v, m));
	n = vec_divis_cst(n, vec_length(n));
	return (n);
}

t_vector	normals(t_data *q, t_obj *fig, t_vector p, t_vector d, double t)
{
	t_vector	oc;

	oc = vec_diff(new_vec(q->camera.x, q->camera.y, q->camera.z), fig->c);
	if (fig->type == SPHERE)
		return (norm_sphere(fig, p));
	if (fig->type == CONE)
		return (norm_cone(oc, t, d, p, fig));
	if (fig->type == CYLINDER)
		return (norm_cyl(oc, t, d, p, fig));
	if (fig->type == PLANE)
	{
		if (vec_dot(d, fig->v) > 0)
			return (rev_vec(fig->v));
		else
			return (fig->v);
	}
	return ((t_vector){0, 0, 0});
}
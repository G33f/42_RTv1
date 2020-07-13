/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:32:30 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/11 20:42:02 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	spec(t_vector n, t_vector l, t_vector v, double s, double i)
{
	t_vector	r;
	double		r_dot_v;

	if (s >= 0)
	{
		r = (vec_diff(vec_mult_cst(vec_mult_cst(n, 2), vec_dot(n, l)), l));
		r_dot_v = vec_dot(r, v);
		if (r_dot_v > 0)
			return(i * pow(r_dot_v / (vec_length(r) * vec_length(v)), s));
		else
			return(0.0);
	}
	else
		return(0.0);
}

double	light_point(t_vector p, t_vector n, t_vector v, double s, t_data *q)
{
	double		n_dot_l;

	q->l_p = vec_diff(q->l_p, p);
	n_dot_l = vec_dot(n, q->l_p);
	if (n_dot_l > 0)
		return((q->intens_p * n_dot_l / (vec_length(n) * vec_length(q->l_p)) + spec(n, q->l_p, v, s, q->intens_p)));
	else
		return(0.0);
}

double	light_direction(t_vector n, t_vector v, double s, t_data *q)
{
	double		n_dot_l;

	n_dot_l = vec_dot(n, q->l_d);
	if (n_dot_l > 0)
		return((q->intens_d * n_dot_l / (vec_length(n) * vec_length(q->l_d)) + spec(n, q->l_d, v, s, q->intens_d)));
	else
		return(0.0);
}

double	light_intens(t_vector p, t_vector n, t_vector v, double s, t_data *q)
{
	return (light_direction(n, v, s, q) + light_point(p, n, v, s, q) + q->ambient);
}

/*int		closest(t_vector p, t_vector *l, double t_min, double t_max)
{
	t_vector	d;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;

	d = vec_diff(p, p->l_p);
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z),
			p->l_p);
	disk = pow((2 * vec_dot(oc, d)), 2) - (4 * vec_dot(d, d) *
			(vec_dot(oc, oc) - pow(o->r, 2)));
	if (disk <= 0)
		return (0);
	t1 = ((-2 * vec_dot(oc, d)) + sqrt(disk)) / (2 * vec_dot(d, d));
	t2 = ((-2 * vec_dot(oc, d)) - sqrt(disk)) / (2 * vec_dot(d, d));
	t1 = min(t1, t2);
	if (t1 < *t && t1 > 0)
	{
		*t = t1;
		return (get_color(t1, p, d, o));
	}
	return (0);
}*/

int get_color(double t, t_data *q, t_vector d, t_orb *o)
{
	t_vector	n;
	t_vector	p;
	double		i;

	p = vec_sum(new_vec(q->camera.x, q->camera.x, q->camera.x),
			vec_mult_cst(d, t));
	n = vec_diff(p, new_vec(o->x, o->y, o->z));
	n = vec_divis_cst(n, vec_length(n));
	i = light_intens(p, n, rev_vec(d),o->specular, q);
	return(color(o->color, i));
}
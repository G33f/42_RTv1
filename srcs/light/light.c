/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:32:30 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/04 07:32:33 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"



double	light_ambient()
{
	double	intens;

	intens = 0.2;
	return(intens);
}

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

double	light_point(t_vector p, t_vector n, t_vector v, double s)
{
	double		intens;
	t_vector	l;
	double		n_dot_l;

	intens = 0.6;
	l = new_vec(2, -1, 0);
	l = vec_diff(l, p);
	n_dot_l = vec_dot(n, l);
	if (n_dot_l > 0)
		return((intens * n_dot_l / (vec_length(n) * vec_length(l)) + spec(n, l, v, s, intens)));
	else
		return(0.0);
}

double	light_direction(t_vector n, t_vector v, double s)
{
	double		intens;
	t_vector	l;
	double		n_dot_l;

	intens = 0.2;
	l = new_vec(1, -4, 4);
	n_dot_l = vec_dot(n, l);
	if (n_dot_l > 0)
		return((intens * n_dot_l / (vec_length(n) * vec_length(l)) + spec(n, l, v, s, intens)));
	else
		return(0.0);
}

double	light_intens(t_vector p, t_vector n, t_vector v, double s)
{
	return (light_direction(n, v, s) + light_point(p, n, v, s) + light_ambient());
}

int get_color(double t, t_data *q, t_vector d, t_orb *o)
{
	t_vector	n;
	t_vector	p;
	double		i;

	p = vec_sum(new_vec(q->camera.x, q->camera.x, q->camera.x),
			vec_mult_cst(d, t));
	n = vec_diff(p, new_vec(o->x, o->y, o->z));
	n = vec_divis_cst(n, vec_length(n));
	i = light_intens(p, n, rev_vec(d),o->specular);
	return(color(o->color, i));
}
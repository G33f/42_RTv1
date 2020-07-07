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

double	light_point(t_vector p, t_vector n)
{
	double		intens;
	t_vector	l;
	double		n_dot_l;

	intens = 0.6;
	l = new_vec(1, 2, 0);
	l = vec_diff(l, p);
	n_dot_l = vec_dot(n, l);
	if (n_dot_l > 0)
		return(intens * n_dot_l / (vec_length(n) * vec_length(l)));
	else
		return(0.0);
}

double	light_direction(t_vector n)
{
	double		intens;
	t_vector	l;
	double		n_dot_l;

	intens = 0.2;
	l = new_vec(1, 4, 4);
	l = rev_vec(l);
	n_dot_l = vec_dot(n, l);
	if (n_dot_l > 0)
		return(intens * n_dot_l / (vec_length(n) * vec_length(l)));
	else
		return(0.0);
}

double	light_intens(t_vector p, t_vector n)
{
	return (light_direction(n) + light_point(p, n) + light_ambient());
}

int get_color(double t, t_data *q, t_vector d, t_orb *o)
{
	t_vector	n;
	t_vector	p;

	p = vec_sum(new_vec(q->camera.x, q->camera.x, q->camera.x),
			vec_mult_cst(d, t));
	n = vec_diff(p, new_vec(o->x, o->y, o->z));
	n = vec_divis_cst(n, vec_length(n));
	return(color(o->color, light_intens(p, n)));
}
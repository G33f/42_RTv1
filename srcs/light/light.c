/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:32:30 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/09 20:42:20 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*double	light_ambient()
{
	double	intens;

	intens = 0.2;
	return(intens);
}*/

double	light_point(t_vector p, t_vector n, t_data *q)
{
	//double		intens;
	//t_vector	l;
	double		n_dot_l;

	//intens = 0.6;
	//l = new_vec(1, 2, 0);
	q->l_p = vec_diff(q->l_p, p);
	n_dot_l = vec_dot(n, q->l_p);
	if (n_dot_l > 0)
		return(q->intens_p * n_dot_l / (vec_length(n) * vec_length(q->l_p)));
	else
		return(0.0);
}

double	light_direction(t_vector n, t_data *q)
{
	//double		intens;
	//t_vector	l;
	double		n_dot_l;

	//intens = 0.2;
	//l = new_vec(1, 4, 4);
	//l = rev_vec(l);
	n_dot_l = vec_dot(n, q->l_d);
	if (n_dot_l > 0)
		return(q->intens_d * n_dot_l / (vec_length(n) * vec_length(q->l_d)));
	else
		return(0.0);
}

double	light_intens(t_vector p, t_vector n, t_data *q)
{
	return (light_direction(n, q) + light_point(p, n, q) + q->ambient);
}

int get_color(double t, t_data *q, t_vector d, t_obj o)
{
	t_vector	n;
	t_vector	p;

	p = vec_sum(new_vec(q->camera.x, q->camera.x, q->camera.x),
			vec_mult_cst(d, t));
	n = vec_diff(p, new_vec(o.x, o.y, o.z));
	n = vec_divis_cst(n, vec_length(n));
	return(color(o.color, light_intens(p, n, q)));
}
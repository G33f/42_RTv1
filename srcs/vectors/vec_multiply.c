/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_multiply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:16:40 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/04 02:16:42 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	rev_vec(t_vector a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	return (a);
}

double		vec_dot(t_vector a, t_vector b)
{
	a = vec_scal_mult(a, b);
	return (a.x + a.y + a.z);
}

t_vector	vec_scal_mult(t_vector a, t_vector b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_vector	vec_mult_cst(t_vector a, double t)
{
	a.x *= t;
	a.y *= t;
	a.z *= t;
	return (a);
}

t_vector	vec_divis_cst(t_vector a, double t)
{
	a.x /= t;
	a.y /= t;
	a.z /= t;
	return (a);
}

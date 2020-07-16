/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 01:05:33 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/04 01:05:37 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		vec_length(t_vector a)
{
	return(sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

t_3_vec		vec_3_init(t_vector p, t_vector n, t_vector v)
{
	t_3_vec	tre;

	tre.p = p;
	tre.n = n;
	tre.v = v;
	return (tre);
}

t_vector	vec_diff(t_vector a, t_vector b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return(a);
}

t_vector	vec_sum(t_vector a, t_vector b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return(a);
}

t_vector	new_vec(double x, double y, double z)
{
	t_vector vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return(vec);
}

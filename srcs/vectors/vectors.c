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

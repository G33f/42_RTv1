/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 04:53:26 by wpoudre           #+#    #+#             */
/*   Updated: 2020/08/06 21:02:10 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	qn_rot(t_data *p, t_qn qn, double agl)
{
	qn.w *= cos(agl);
	qn.x *= sin(agl);
	qn.y *= sin(agl);
	qn.z *= sin(agl);
	p->rot = qn_sum(p->rot, qn);
}

t_qn	rotate_e(t_qn vec, t_data *p)
{
	t_qn	rev_rot;

	vec = qn_sum(p->rot, vec);
	rev_rot = qn_min(p->rot);
	magn(&rev_rot);
	vec = qn_sum(vec, rev_rot);
	return (vec);
}

void	rot(t_vector *p1, t_data *p)
{
	t_qn vec;

	vec = (t_qn){0, p1->x, p1->y, p1->z};
	vec = rotate_e(vec, p);
	p1->x = vec.x;
	p1->y = vec.y;
	p1->z = vec.z;
}

void	rotation(t_data *p)
{
	qn_rot(p, (t_qn){1, 1, 0, 0}, p->camera.rot_x);
	qn_rot(p, (t_qn){1, 0, 1, 0}, p->camera.rot_y);
	qn_rot(p, (t_qn){1, 0, 0, 1}, p->camera.rot_z);
}

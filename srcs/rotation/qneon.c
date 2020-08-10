/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qneon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 04:53:13 by wpoudre           #+#    #+#             */
/*   Updated: 2020/08/01 04:53:14 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_qn	qn_min(t_qn qn)
{
	if (qn.x != 0)
		qn.x *= -1;
	if (qn.y != 0)
		qn.y *= -1;
	if (qn.z != 0)
		qn.z *= -1;
	return (qn);
}

t_qn	qn_sum(t_qn q1, t_qn q2)
{
	t_qn	res;

	res.w = q1.w * q2.w - (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);
	res.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	res.y = q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z;
	res.z = q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x;
	return (res);
}

void	magn(t_qn *st)
{
	int	magn;

	magn = sqrt(pow(st->x, 2) + pow(st->y, 2) + pow(st->z, 2) + pow(st->w, 2));
	st->x = st->x / magn;
	st->y = st->y / magn;
	st->z = st->z / magn;
	st->w = st->w / magn;
}

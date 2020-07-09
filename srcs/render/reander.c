/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reander.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 21:06:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/09 19:48:13 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	ray_tracing(t_data *p, t_vector r, t_obj o)
{
	t_vector	d;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;

	d = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z),
			new_vec(o.x, o.y, o.z));
	disk = pow((2 * vec_dot(oc, d)), 2) - (4 * vec_dot(d, d) *
			(vec_dot(oc, oc) - pow(o.r, 2)));
	if (disk <= 0)
		return (0);
	t1 = ((-2 * vec_dot(oc, d)) + sqrt(disk)) / (2 * vec_dot(d, d));
	t2 = ((-2 * vec_dot(oc, d)) - sqrt(disk)) / (2 * vec_dot(d, d));
	if (t1 > 0 || t2 > 0)
	{
		if (t1 < t2 && t1 > 0)
			return (get_color(t1, p, d, o));
		else if (t1 > t2 && t2 > 0)
			return (get_color(t2, p, d, o));
	}
	return(0);
}

int render(t_data *p, t_obj obj)
{
	int i;
	int j;
	int x;
	int y;

	ft_putstr("render\n");
	y = p->camera.x - p->camera.canv_h / 2;
	i = 0;
	while(y < p->camera.y + p->camera.canv_h / 2)
	{
		j = 0;
		x = p->camera.x - p->camera.canv_w / 2;
		while(x < p->camera.x + p->camera.canv_w / 2)
		{
			p->canv.img_data[i * p->camera.canv_w + j] = ray_tracing(p,
					new_vec(x, y, p->camera.canv_d), obj);
			x++;
			j++;
		}
		y++;
		i++;
	}
	return(0);
}

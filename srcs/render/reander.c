/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reander.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 21:06:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/03 21:06:12 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	min(double a, double b, t_t *t)
{
	if (a < b && a > t->t_min && a < t->t_max)
		return (a);
	else if (b > t->t_min && b < t->t_max)
		return (b);
	return (0.0);
}

int	ray_tracing(t_data *p, t_vector r, t_obj *o, t_t *t)
{
	t_vector	d;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;

	d = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z), o->c);
	disk = f_disk(d, oc, o);
	if (disk <= 0)
		return (0);
	t1 = ((-2 * vec_dot(oc, d)) + sqrt(disk)) / (2 * vec_dot(d, d));
	t2 = ((-2 * vec_dot(oc, d)) - sqrt(disk)) / (2 * vec_dot(d, d));
	t1 = min(t1, t2, t);
	if (t1 < t->t_max && t1 > t->t_min)
	{
		t->t_max = t1;
		return (get_color(t1, p, d, o));
	}
	return (0);
}

void	render_cy(t_data *p, t_vector r, int j)
{
	t_list	*f;
	t_obj	o;
	int		color;
	int		buf;
	t_t		t;

	f = p->figur;
	color = 0;
	t.t_min = 0;
	t.t_max = 2147483647;
	while(f != NULL)
	{
		o = obj_clon(f);
		buf = ray_tracing(p, new_vec(r.x, r.y, p->camera.canv_d), &o, &t);
		if (buf > 0)
			color = buf;
		f = f->next;
	}
	p->canv.img_data[(int)r.z * p->camera.canv_w + j] = color;
}

int render(t_data *p)
{
	int i;
	int j;
	int x;
	int	y;

	y = p->camera.x - p->camera.canv_h / 2;
	i = 0;
	while(y < p->camera.y + p->camera.canv_h / 2)
	{
		j = 0;
		x = p->camera.x - p->camera.canv_w / 2;
		while(x < p->camera.x + p->camera.canv_w / 2)
		{
			render_cy(p, new_vec(x, y, i), j);
			x++;
			j++;
		}
		y++;
		i++;
	}
	return(0);
}

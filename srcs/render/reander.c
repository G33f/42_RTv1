/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reander.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 21:06:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/08/06 21:02:35 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	min(double a, double b)
{
	if (a < b && a >= 0)
		return (a);
	else if (b >= 0)
		return (b);
	return (0.0);
}

double	max(double a, double b)
{
	if (a > b && a >= 0)
		return (a);
	if (b >= 0)
		return (b);
	return (0.0);
}

t_res	ray_tracing(t_data *p, t_vector r, t_obj *o, t_t *t)
{
	t_vector	d;
	t_vector	oc;
	double		tl[2];
	double		*k;

	d = vec_diff(r, (t_vector){p->camera.x, p->camera.y, p->camera.z});
	rot(&d, p);
	d = vec_divis_cst(d, vec_length(d));
	oc = vec_diff((t_vector){p->camera.x, p->camera.y, p->camera.z}, o->c);
	o->v = vec_divis_cst(o->v, vec_length(o->v));
	k = f_disk(d, oc, o, tl);
	if (k[0] < t->t_max && k[0] > t->t_min)
		return ((t_res){d, *o, k[0]});
	return ((t_res){(t_vector) {0, 0, 0}, *o, t->t_max});
}

void	render_cy(t_data *p, t_vector r, int j)
{
	t_list			*f;
	static t_obj	o;
	t_res			buf;
	t_res			res;
	t_t				t;

	f = p->figur;
	t.t_min = 0.0;
	t.t_max = 2147483647.0;
	res = (t_res){(t_vector) {0, 0, 0}, o, t.t_max};
	while (f != NULL)
	{
		o = obj_clon(f);
		buf = ray_tracing(p, new_vec(r.x, r.y, p->camera.canv_d), &o, &t);
		if (buf.t < res.t && buf.t > t.t_min)
			res = buf;
		f = f->next;
	}
	if (res.t == t.t_max)
		p->canv.img_data[(int)r.z * p->camera.canv_w + j] = 0x000000;
	else
		p->canv.img_data[(int)r.z * p->camera.canv_w + j] = get_color(
				res.t, p, res.d, &res.o);
}

int		render(t_data *p)
{
	int i;
	int j;
	int x;
	int	y;

	//qn_rot(p, (t_qn){1, 1, 0, 0}, 0.2);
	//qn_rot(p, (t_qn){1, 0, 0, 1}, 0.7);
	rotation(p);	
	y = p->camera.y - p->camera.canv_h / 2;
	i = 0;
	while (y < p->camera.y + p->camera.canv_h / 2)
	{
		j = 0;
		x = p->camera.x - p->camera.canv_w / 2;
		while (x < p->camera.x + p->camera.canv_w / 2)
		{
			render_cy(p, new_vec(x, y, i), j);
			x++;
			j++;
		}
		y++;
		i++;
	}
	return (0);
}

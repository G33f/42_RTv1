/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reander.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 21:06:09 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/17 12:48:05 by mgalt            ###   ########.fr       */
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

/*t_plane	plane_clon(const t_list *o)
{
	t_plane	p;

	p.x = ((t_plane*)o->content)->x;
	p.y = ((t_plane*)o->content)->y;
	p.z = ((t_plane*)o->content)->z;
	p.n = ((t_plane*)o->content)->n;
	p.color = ((t_plane*)o->content)->color;
	return(p);
}*/

int	ray_tracing(t_data *p, t_vector r, t_obj *o, t_t *t)
{
	t_vector	d;
	t_vector	oc;
	double		tl[2];
	double		*k;

	d = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	d = vec_divis_cst(d, vec_length(d));
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z), o->c);
	k = f_disk(d, oc, o, tl);
	if (o->type == PLANE)
	{
		if (vec_dot(d, o->v) > 0.000001)
		{
			tl[0] = (-1 * vec_dot(oc, o->v)) / vec_dot(d, o->v);
			if (tl[0] < t->t_max && tl[0] > t->t_min)
			{
				t->t_max = tl[0];
				return (get_color(tl[0], p, d, o));
			}
		}
		else
			return (0);
	}
	if (k[0] < t->t_max && k[0] > t->t_min)
	{
		t->t_max = k[0];
		return (get_color(k[0], p, d, o));
//		return (color(0xFFFFFF, 2/k[0]));
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

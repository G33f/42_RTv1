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

double	min(double a, double b, t_t *t)
{
	if (a < b && a > t->t_min && a < t->t_max)
		return (a);
	else if (b > t->t_min && b < t->t_max)
		return (b);
	/*else if (a > b && b < t->t_min && a < t->t_max && a > t->t_min)
		return (a);*/
	return (0.0);
}

/*int	ray_tracing(t_data *p, t_vector r, t_orb *o, t_t *t)
{
	t_vector	d;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;

	d = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z),
			new_vec(o->x, o->y, o->z));
	disk = pow((2 * vec_dot(oc, d)), 2) - (4 * vec_dot(d, d) *
			(vec_dot(oc, oc) - pow(o->r, 2)));
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
}*/

/*int	ray_tracing_pl(t_data *p, t_vector r, t_plane *o, t_t *b)
{
	t_vector	l0;
	//t_vector	oc;
	t_vector	l;
	t_vector	p0l0;
	t_vector	p0;
	//t_vector	p1;
	double		t;
	double f;

	b->t_max = b->t_max;
	//l = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	l0 = new_vec(p->camera.x, p->camera.y, p->camera.z);
	l = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	//oc = vec_diff(l0, new_vec(o->x, o->y, o->z));
	p0 = new_vec(o->x, o->y, o->z);
	f = vec_dot(o->n, l);
	if (f > 0.000001)
	{
		p0l0 = vec_diff(l0, p0);
		t = vec_dot(p0l0, o->n);
		if (t >= 0)
		{
			//p1 = vec_sum(vec_mult_cst(l, t), l0);
			return (get_color_pl(t, p, l, l0, o));
		}
	}
	return (0);
}

t_plane	plane_clon(const t_list *o)
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
	double		disk;
	double		t1;
	double		t2;

/*//	r = vec_divis_cst(r, vec_length(r));
	d = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	d = vec_divis_cst(d, vec_length(d));
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z), o->c);
//	oc = vec_rev(oc);
	disk = f_disk(d, oc, o);*/
	d = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	d = vec_divis_cst(d, vec_length(d));
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z), o->c);
	disk = f_disk(d, oc, o);
	if (disk <= 0 && o->type != PLANE)
		return (0);
	else if (o->type == PLANE)
	{
		//t1 = rt_plane(p, r, d, oc);
		if (vec_dot(d, o->v) > 0.000001)
		{
			t1 = (-1 * vec_dot(oc, o->v)) / vec_dot(d, o->v);
			if (t1 < t->t_max && t1 > t->t_min)
			{
				t->t_max = t1;
				return (get_color(t1, p, d, o));
			}
		}
		else
			return (0);
	}
	t1 = ((-2 * vec_dot(oc, d)) + sqrt(disk)) / (2 * vec_dot(d, d));
	t2 = ((-2 * vec_dot(oc, d)) - sqrt(disk)) / (2 * vec_dot(d, d));
	t1 = min(t1, t2, t);
	if (t1 < t->t_max && t1 > t->t_min)
	{
		t->t_max = t1;
//		printf("%d = %f\n", o->type, t1);
//		return (color(0xFFFFFF, 2/t1));

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
	t.t_min = 0.000001;
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

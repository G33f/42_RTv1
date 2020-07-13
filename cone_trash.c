t_cone	*new_cone(t_cone new)
{
	t_cone	*co;

	co = (t_cone*)malloc(sizeof(t_cone));
	co->x = new.x;
	co->y = new.y;
	co->z = new.z;
	co->r = new.r;
	co->vx = new.vx;
	co->vy = new.vy;
	co->vz = new.vz;
	co->specular = new.specular;
	co->color = new.color;
	co->next = NULL;
	return (co);
}

t_cone	cone_init(int x, int y, int z, int vx, int vy, int vz, int r, int color, double spec)
{
	t_cone	cone;

	cone.x = x;
	cone.y = y;
	cone.z = z;
	cone.vx = vx;
	cone.vy = vy;
	cone.vz = vz;
	cone.r = r;
	cone.color = color;
	cone.specular = spec;
	return (cone);
}

void	figur_init(t_data *p)
{
	t_cone	c1;
	/*t_orb	o2;
	t_orb	o3;
	t_orb	o4;*/

	p->figur = NULL;
	c1 = cone_init(0, 0, 0, 0, 1, 0, 1, 0xFF0000, 500);
	ft_lstadd(&p->figur, ft_lstnew(new_cone(c1), sizeof(t_orb)));
	ft_putstr("after lstadd\n");
	/*o2 = orb_init(2, 0, 4, 1, 0x0000FF, 500);
	ft_lstadd(&p->figur, ft_lstnew(new_orb(o2), sizeof(t_orb)));
	o3 = orb_init(-2, 0, 4, 1, 0x00FF00, 10);
	ft_lstadd(&p->figur, ft_lstnew(new_orb(o3), sizeof(t_orb)));
	o4 = orb_init(0, 5001, 0, 5000, 0xFFFF00, 1000);
	ft_lstadd(&p->figur, ft_lstnew(new_orb(o4), sizeof(t_orb)));*/
}

/*double	min(double a, double b)
{
	if (a < b && a > 0)
		return (a);
	else if (b > 0)
		return (b);
	return (0.0);
}*/

t_cone	*cone_clon(const t_list *o)
{
	t_cone *orb;

	orb = (t_cone*)malloc(sizeof(t_cone));
	orb->x = ((t_cone*)o->content)->x;
	orb->y = ((t_cone*)o->content)->y;
	orb->z = ((t_cone*)o->content)->z;
	orb->r = ((t_cone*)o->content)->r;
	orb->vx = ((t_cone*)o->content)->vx;
	orb->vy = ((t_cone*)o->content)->vy;
	orb->vz = ((t_cone*)o->content)->vz;
	orb->specular = ((t_cone*)o->content)->specular;
	orb->color = ((t_cone*)o->content)->color;
	return(orb);
}

/*int		ray_tracing_cyl(t_data *p, t_vector r, t_cyl *c, double *t)
{
	t_vector	d;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;
}*/

int get_color_cone(double t, t_data *q, t_vector d, t_cone *o)
{
	t_vector	n;
	t_vector	p;
	double		i;

	p = vec_sum(new_vec(q->camera.x, q->camera.x, q->camera.x),
			vec_mult_cst(d, t));
	n = vec_diff(p, new_vec(o->x, o->y, o->z));
	n = vec_divis_cst(n, vec_length(n));
	i = light_intens(p, n, rev_vec(d),o->specular, q);
	return(color(o->color, i));
}

int	ray_tracing_cone(t_data *p, t_vector r, t_cone *o, double *t)
{
	t_vector	d;
	t_vector	v;
	t_vector	oc;
	double		disk;
	double		t1;
	double		t2;
	double k1, k2, k3;
	//double angle = 0.523599;

	r.x = 0;
	//d = vec_diff(r, new_vec(p->camera.x, p->camera.y, p->camera.z));
	d = new_vec(o->vx, o->vy, o->vz);
	//co = vec_diff(new_vec(o->x, o->y, o->z), new_vec(p->camera.x, p->camera.y, p->camera.z));
	//d = vec_diff(r, new_vec(o->vx, o->vy, o->vz));
	//d = new_vec(o->vx, o->vy, o->vz);
	//oc = vec_diff(new_vec(o->vx, o->vy, o->vz),
			//new_vec(o->x, o->y, o->z));
	oc = vec_diff(new_vec(p->camera.x, p->camera.y, p->camera.z),
			new_vec(o->x, o->y, o->z));
	//disk = pow((2 * vec_dot(oc, d)), 2) - (4 * vec_dot(d, d) *
	//		(vec_dot(oc, oc) - pow(o->r, 2)));
	v = new_vec(o->vx, o->vy, o->vz);
	k2 = pow((2*oc.x*d.x+2*oc.y*d.y-2*oc.z*d.z), 2);
	k1 = d.x*d.x + d.y*d.y - d.z*d.z;
	k3 = oc.x*oc.x + oc.y*oc.y - oc.z*oc.z;
	//k1 = pow(vec_dot(d, v), 2) - pow(cos(angle), 2);
	//k2 = 
	//k3 = 
	disk = k2 * k2 - 4 * k1 * k3;
	if (disk <= 0)
		return (0);
	//t1 = ((-2 * vec_dot(oc, d)) + sqrt(disk)) / (2 * vec_dot(d, d));
	//t2 = ((-2 * vec_dot(oc, d)) - sqrt(disk)) / (2 * vec_dot(d, d));
	t1 = (-k2 + sqrt(disk)) / (2 * k1);
	t2 = (-k2 - sqrt(disk)) / (2 * k1);
	t1 = min(t1, t2);
	if (t1 < *t && t1 > 0)
	{
		*t = t1;
		return (get_color_cone(t1, p, d, o));
	}
	return (0);
}

void	render_cone2(t_data *p, t_vector r, int j)
{
	t_list	*f;
	t_cone	*o;
	int		color;
	int		buf;
	double	t;

	f = p->figur;
	color = 0;
	t = 2147483647;
	while(f != NULL)
	{
		o = cone_clon(f);
		buf = ray_tracing_cone(p, new_vec(r.x, r.y, p->camera.canv_d), o, &t);
		if (buf > 0)
			color = buf;
		free(o);
		f = f->next;
	}
	p->canv.img_data[(int)r.z * p->camera.canv_w + j] = color;
}

int render_cone(t_data *p)
{
	int i;
	int j;
	int x;
	int	y;

	y = p->camera.x - p->camera.canv_h / 2;
	//printf("cam x: %f canv_h: %d y: %d\n", p->camera.x, p->camera.canv_h, y);
	i = 0;
	while(y < p->camera.y + p->camera.canv_h / 2)
	{
		j = 0;
		x = p->camera.x - p->camera.canv_w / 2;
		while(x < p->camera.x + p->camera.canv_w / 2)
		{
			render_cone2(p, new_vec(x, y, i), j);
			x++;
			j++;
		}
		y++;
		i++;
	}
	return(0);
}


void	test(t_data *p)
{
	figur_init(p);
	render_cone(p);
	drow(p);
}

int main()
{
	t_data	p;

	init(&p);
	test(&p);
	mlx_put_image_to_window(p.mlx.mlx, p.mlx.win, p.img.img, 0, 0);
	mlx_hook(p.mlx.win, 2, 0, key_press, &p);
	mlx_hook(p.mlx.win, 17, 1L << 17, escape, &p);
	mlx_loop(p.mlx.mlx);
	return(0);
}

/*int main(int ac, char **av)
{
	t_data	p;

	if (ac == 2)
	{
		if ((read_file(&p, av[1])) == -1)
			return (0);
		mlx_put_image_to_window(p.mlx.mlx, p.mlx.win, p.img.img, 0, 0);
		mlx_hook(p.mlx.win, 2, 0, key_press, &p);
		mlx_hook(p.mlx.win, 17, 1L << 17, escape, &p);
		mlx_loop(p.mlx.mlx);
	}
	else
		ft_putstr("\nUsage: ./RTv1 <scene>\n\n");
	return(0);
}*/
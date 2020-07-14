void *render(void *tmp)
{
	int i;
	int j;
	//int x;
	//int	y;
	t_data	*p;

	p = (t_data*)tmp;
	p->y = p->camera.x - p->camera.canv_h / 2;
	i = 0;
	while(p->y < p->camera.y + p->camera.canv_h / 2)
	{
		j = 0;
		p->x = p->camera.x - p->camera.canv_w / 2;
		while(p->x < p->max_x - 1)
		{
			render_cy(p, new_vec(p->x, p->y, i), j);
			p->x++;
			j++;
		}
		p->y++;
		i++;
	}
	return(NULL);
}

void	create_thread(t_data *p)
{
	pthread_t	t[THREADS];
	int			i;
	t_data		tmp[THREADS];

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void*)&tmp[i], (void*)p, sizeof(t_data));
		tmp[i].x = THREAD_WIDTH * i;
		tmp[i].max_x = THREAD_WIDTH * (i + 1);
		pthread_create(&t[i], NULL, render, &tmp[i]);
		i++;
	}
	while (i > 0)
	{
		pthread_join(t[i], NULL);
		i--;
	}
}

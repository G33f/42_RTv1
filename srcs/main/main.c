/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:16:15 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/09 20:53:12 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
}

int		escape(void)
{
	exit(1);
	return (0);
}

int		key_press(int key, t_data *p)
{
	p = NULL;
	if (key == 53)
		exit(escape());
	return (0);
}

/*void	test(t_data *p)
{
	t_orb o;

	o = orb_init(0, 0, 3, 1, 0xFF0000);
	render(p, &o);
	drow(p);
}*/

int		object_num(char *file)
{
	int		fd;
	char	*line;
	int		n;

	n = 0;
	fd = open(file, O_RDONLY);
	while ((get_next_line(fd, &line)) > 0)
	{
		if ((ft_strncmp(line, "sphere", 6)) == 0 || (ft_strncmp(line, "cylinder", 8)) == 0 ||
		(ft_strncmp(line, "cone", 4)) == 0 || (ft_strncmp(line, "plane", 5)) == 0)
			n++;
		free(line);
	}
	close(fd);
	return (n);
}

/*void	parse_figure(t_data *p, char **tab, t_obj *obj)
{
	char	**tab1;

	tab1 = NULL;
	p = NULL;
	if (ft_strequ(tab[0], "sphere"))
		obj->type = 1;
	else if (ft_strequ(tab[0], "cylinder"))
		obj->type = 2;
	else if (ft_strequ(tab[0], "cone"))
		obj->type = 3;
	else if (ft_strequ(tab[0], "plane"))
		obj->type = 4;
	printf("object type: %d\n", obj->type);
	tab1 = ft_strsplit(tab[1], ',');
	obj->x = ft_atoi(tab1[0]);
	obj->y = ft_atoi(tab1[1]);
	obj->z = ft_atoi(tab1[2]);
	obj->r = strtod(tab1[3], NULL);
	obj->color = ft_atoi(tab1[4]);
	//printf("%d %d %d %f %d\n", obj->x, obj->y, obj->z, obj->r, obj->color);
	free_tab(tab1);
}*/

int		camera(t_data *p, char **tab)
{
	char	**tab1;

	tab1 = NULL;
	tab1 = ft_strsplit(tab[1], ',');
	if (len_tab(tab1) < 6)
	{
		free_tab(tab1);
		return (-1);
	}
	p->camera.canv_h = ft_atoi(tab1[0]);
	p->camera.canv_w = ft_atoi(tab1[1]);
	p->camera.canv_d = ft_atoi(tab1[2]);
	p->camera.x = strtod(tab1[3], NULL);
	p->camera.y = strtod(tab1[4], NULL);
	p->camera.z = strtod(tab1[5], NULL);
	//printf("%d %d %d %f %f %f\n", p->camera.canv_h, p->camera.canv_w, p->camera.canv_d, p->camera.x, p->camera.y, p->camera.z);
	free_tab(tab1);
	return (0);
}

/*void	check_line(t_data *p, char *line, t_obj *obj)
{
	char	**tab;

	tab = NULL;
	//p = NULL;
	//obj = NULL;
	tab = ft_strsplit(line, ' ');
	//printf("Tab[0] is %s\n", tab[0]);
	if (ft_strequ(tab[0], "sphere") || ft_strequ(tab[0], "cone") ||
	ft_strequ(tab[0], "cylinder") || ft_strequ(tab[0], "plane"))
		parse_figure(p, tab, obj);
	if (ft_strequ(tab[0], "camera"))
		camera(tab, p);
	if (!(ft_strcmp(tab[0], "light")))
		hfgh();
	if (!(ft_strcmp(tab[0], "ambient")))
		p->ambient = strtod(tab[1], NULL);
	free_tab(tab);
}*/

int		len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

int		sphere(t_data *p, int *n, char *line)
{
	int		i;
	//char	*l;
	char	**tab1;
	int		tab_len;

	i = 0;
	*n += 1;
	p->obj[*n].type = SPHERE;
	tab1 = NULL;
	tab1 = ft_strsplit(line, ',');
	tab_len = len_tab(tab1);
	if (tab_len < 5)
		return (-1);
	p->obj->x = ft_atoi(tab1[0]);
	p->obj->y = ft_atoi(tab1[1]);
	p->obj->z = ft_atoi(tab1[2]);
	p->obj->r = strtod(tab1[3], NULL);
	p->obj->color = ft_atoi(tab1[4]);
	//printf("%d %d %d %f %d\n", obj->x, obj->y, obj->z, obj->r, obj->color);
	free_tab(tab1);
	return (0);
}

int		set_light(t_data *p, char **tab)
{
	char	**tab1;

	ft_putstr("set light\n");
	tab1 = ft_strsplit(tab[2], ',');
	printf("len_tab in light = %d\n", len_tab(tab1));
	if (len_tab(tab1) < 4)
	{
		free_tab(tab1);
		return (-1);
	}
	if (ft_strequ(tab[0], "light") && ft_strequ(tab[1], "point"))
	{
		ft_putstr("l_p, intens\n");
		p->l_p = new_vec(ft_atoi(tab1[0]), ft_atoi(tab1[1]), ft_atoi(tab1[2]));
		ft_putstr("l_p, intens after new vec\n");
		p->intens_p = strtod(tab1[3], NULL);
		ft_putstr("l_p, intens\n");
	}
	if (ft_strequ(tab[0], "light") && ft_strequ(tab[0], "direction"))
	{
		p->l_d = new_vec(ft_atoi(tab1[0]), ft_atoi(tab1[1]), ft_atoi(tab1[2]));
		p->l_d = rev_vec(p->l_d);
		p->intens_d = strtod(tab1[3], NULL);
	}
	free_tab(tab1);
	return (0);
}

int		create_obj(t_data *p, char *line, int *n) // какой именно объект
{
	//char	*l;
	char	**tab;

	//ft_putstr("create_obj\n");
	tab = NULL;
	tab = ft_strsplit(line, ' ');
	if (ft_strequ(tab[0], "sphere"))
		sphere(p, n, tab[1]);
	/*if (ft_strequ(tab[0], "cylinder"))
		cylinder(p, n);
	if (ft_strequ(tab[0], "cone"))
		cone(p, n);
	if (ft_strequ(tab[0], "plane"))
		plane(p, n);*/
	if (ft_strequ(tab[0], "camera"))
		camera(p, tab);
	if (ft_strequ(tab[0], "light"))
	{
		set_light(p, tab);
		ft_putstr("after set light\n");
	}
	if (ft_strequ(tab[0], "ambient"))
		p->ambient = strtod(tab[1], NULL);
	/*if (ft_strequ(tab[0], "specular"))
		p->specular = strtod(tab[1], NULL);*/
	return (0);
}

int		read_file(t_data *p, char *file)
{
	char	*line;
	int		i;
	int		n;

	i = 0;
	p->obj_n = object_num(file);
	n = -1;
	if (!p->obj_n)
	{
		ft_putstr("File is invalid\n");
		return (-1);
	}
	if (!(p->obj = (t_obj*)malloc(sizeof(t_obj) * (p->obj_n + 1))))
	{
		ft_putstr("Memory allocation error\n");
		return (-1);
	}
	printf("Obj_num: %d\n", p->obj_n);
	p->obj[p->obj_n].type = 5;
	ft_putstr("after obj num\n");
	if ((p->fd = open(file, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(p->fd, &line)) > 0)
	{
		i++;
		create_obj(p, line, &n);
		//check_line(p, line, p->obj);
		//ft_putstr("in a loop\n");
		free(line);
	}
	ft_putstr("after create object\n");
	p->line_nbr = i;
	printf("%d %d %d %f %d %d\n", p->obj[0].x, p->obj[0].y, p->obj[0].z, p->obj[0].r, p->obj[0].color, p->obj[0].type);
	printf("%f %f %f\n%d %d %d\n", p->camera.x, p->camera.x, p->camera.x, p->camera.canv_h, p->camera.canv_w, p->camera.canv_d);
	init(p);
	close(p->fd);
	render(p, p->obj[0]);
	drow(p);
	free(p->obj);
	return (0);
}

int main(int ac, char **av)
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
}

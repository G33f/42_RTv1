/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:16:15 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/08 18:10:26 by mgalt            ###   ########.fr       */
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

void 	print_vec(t_vector v)
{
	printf("x = %f\ny = %f\nz = %f\n", v.x, v.y, v.z);
}

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

void	parse_figure(t_data *p, char **tab, t_obj *obj)
{
	char	**tab1;

	tab1 = NULL;
	p = NULL;
	tab1 = ft_strsplit(tab[1], ',');
	obj->x = ft_atoi(tab1[0]);
	obj->y = ft_atoi(tab1[1]);
	obj->z = ft_atoi(tab1[2]);
	//obj->r = ft_atoi(tab1[3]);
	obj->r = 1.0;
	obj->color = ft_atoi(tab1[4]);
	//printf("%d %d %d %f %d\n", obj->x, obj->y, obj->z, obj->r, obj->color);
	free_tab(tab1);
}

void	camera(char **tab, t_data *p)
{
	char	**tab1;

	tab1 = NULL;
	tab1 = ft_strsplit(tab[1], ',');
	p->camera.canv_h = ft_atoi(tab1[0]);
	p->camera.canv_w = ft_atoi(tab1[1]);
	p->camera.canv_d = ft_atoi(tab1[2]);
	p->camera.x = strtod(tab1[3], NULL);
	p->camera.y = strtod(tab1[4], NULL);
	p->camera.z = strtod(tab1[5], NULL);
	//printf("%d %d %d %f %f %f\n", p->camera.canv_h, p->camera.canv_w, p->camera.canv_d, p->camera.x, p->camera.y, p->camera.z);
	free_tab(tab1);
}

void	check_line(t_data *p, char *line, t_obj *obj)
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
	/*if (!(ft_strcmp(tab[0], "light")))
		hfgh();*/
	if (!(ft_strcmp(tab[0], "ambient")))
		p->ambient = strtod(tab[1], NULL);
	free_tab(tab);
}

int		read_file(t_data *p, char *file)
{
	char	*line;
	int		i;
	t_obj	*obj;

	i = 0;
	p->obj_n = object_num(file);
	if (!p->obj_n)
	{
		ft_putstr("File is invalid\n");
		return (-1);
	}
	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
	{
		ft_putstr("Memory allocation error\n");
		return (-1);
	}
	printf("Obj_num: %d\n", p->obj_n);
	if (!(p->fd = open(file, O_RDONLY)))
		return (-1);
	while ((get_next_line(p->fd, &line)) > 0)
	{
		i++;
		check_line(p, line, obj);
		free(line);
	}
	p->line_nbr = i;
	init(p);
	close(p->fd);
	render(p, obj);
	drow(p);
	free(obj);
	return (0);
}

/*void	test(t_data *p, char **av)
{
	t_orb o;

	//o = orb_init(0, 0, 3, 1, 0xFF0000);
	//o = orb_init(ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]), ft_atoi(av[4]), 16711680);
	//render(p, &o);
	//drow(p);
}*/

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


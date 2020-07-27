/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:06:23 by mgalt             #+#    #+#             */
/*   Updated: 2020/07/16 20:48:51 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		object_num(char *file)
{
	int		fd;
	char	*line;
	int		n;

	n = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr("Error: cannot open file\n");
		return (-1);
	}
	while ((get_next_line(fd, &line)) > 0)
	{
		if ((ft_strncmp(line, "sphere", 6)) == 0 ||
		(ft_strncmp(line, "cylinder", 8)) == 0 ||
		(ft_strncmp(line, "cone", 4)) == 0 ||
		(ft_strncmp(line, "plane", 5)) == 0)
			n++;
		free(line);
	}
	close(fd);
	return (n);
}

int		find_type(char *type)
{
	int		t;

	t = 0;
	if (ft_strequ(type, "sphere"))
		t = SPHERE;
	else if (ft_strequ(type, "cone"))
		t = CONE;
	else if (ft_strequ(type, "cylinder"))
		t = CYLINDER;
	else if (ft_strequ(type, "plane"))
		t = PLANE;
	return (t);
}

int		figur_init(t_data *p, char *type, char *line)
{
	t_obj	o1;
	t_obj	*o2;
	char	**tab1;
	int		tab_len;
	int		t;

	tab1 = NULL;
	tab1 = ft_strsplit(line, ',');
	tab_len = len_tab(tab1);
	t = find_type(type);
	if (tab_len < 10 || !t)
	{
		free_tab(tab1);
		return (-1);
	}
	o1 = obj_init1(new_vec(ft_atoi(tab1[0]), ft_atoi(tab1[1]),
	ft_atoi(tab1[2])), new_vec(ft_strtodbl(tab1[3]),
	ft_strtodbl(tab1[4]), ft_strtodbl(tab1[5])),
	ft_strtodbl(tab1[6]), ft_strtodbl(tab1[7]));
	o1 = obj_init2(o1, ft_strtodbl(tab1[8]), tab1[9], t);
	o2 = new_obj(o1);
	ft_lstadd(&p->figur, ft_lstnew(o2, sizeof(t_obj)));
	free(o2);
	free_tab(tab1);
	return (0);
}

int		create_obj(t_data *p, char *line)
{
	char	**tab;

	tab = NULL;
	tab = ft_strsplit(line, ' ');
	if (ft_strequ(tab[0], "sphere") || ft_strequ(tab[0], "cylinder") ||
	ft_strequ(tab[0], "cone") || ft_strequ(tab[0], "plane"))
		figur_init(p, tab[0], tab[1]);
	if (ft_strequ(tab[0], "camera"))
		camera(p, tab);
	if (ft_strequ(tab[0], "light"))
		set_light(p, tab);
	if (ft_strequ(tab[0], "ambient"))
		p->l.ambient = ft_strtodbl(tab[1]);
	if (ft_strequ(tab[0], "shadows"))
		p->l.shadows = ft_atoi(tab[1]);
	free_tab(tab);
	return (0);
}

int		read_file(t_data *p, char *file)
{
	char	*line;
	int		i;

	i = 0;
	p->obj_n = object_num(file);
	p->figur = NULL;
	p->light = NULL;
	if (!p->obj_n)
	{
		ft_putstr("File is invalid: no objects found\n");
		return (-1);
	}
	if ((p->fd = open(file, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(p->fd, &line)) > 0)
	{
		create_obj(p, line);
		free(line);
	}
	init(p);
	close(p->fd);
	render(p);
	drow(p);
	return (0);
}

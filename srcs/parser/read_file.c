/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:06:23 by mgalt             #+#    #+#             */
/*   Updated: 2020/07/13 16:24:30 by mgalt            ###   ########.fr       */
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

int		len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

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
		if ((ft_strncmp(line, "sphere", 6)) == 0 || (ft_strncmp(line, "cylinder", 8)) == 0 ||
		(ft_strncmp(line, "cone", 4)) == 0 || (ft_strncmp(line, "plane", 5)) == 0)
			n++;
		free(line);
	}
	close(fd);
	return (n);
}

int		cone_init(t_data *p, int *n, char *line)
{
	t_orb	o1;
    t_orb   *o2;
	char	**tab1;
	int		tab_len;
	int		i;

	i = 0;
	*n += 1;
	p->obj[*n].type = CONE;
	tab1 = NULL;
	tab1 = ft_strsplit(line, ',');
	tab_len = len_tab(tab1);
	if (tab_len < 6)
	{
		free_tab(tab1);
		return (-1);
	}
	o1 = orb_init(ft_atoi(tab1[0]), ft_atoi(tab1[1]), ft_atoi(tab1[2]),
	strtod(tab1[3], NULL), strtod(tab1[4], NULL), ft_atoi(tab1[5]), CONE);
	//printf("%d, %d, %d, %f, %f, %d, %d\n", ft_atoi(tab1[0]), ft_atoi(tab1[1]), ft_atoi(tab1[2]),
	//strtod(tab1[3], NULL), strtod(tab1[4], NULL), ft_atoi(tab1[5]), CONE);
	//printf("o1: %d, %d, %d, %f, %d, %f, %d\n", o1.x, o1.y, o1.z, o1.r, o1.color, o1.specular, o1.type);
    o2 = new_orb(o1);
	ft_lstadd(&p->figur, ft_lstnew(o2, sizeof(t_orb)));
	//printf("o2: %d %d %d %f %f %d %d\n", o2->x, o2->y, o2->z, o2->r, o2->specular, o2->color, o2->type);
    free(o2);
	free_tab(tab1);
	return (0);
}

int		create_obj(t_data *p, char *line, int *n)
{
	char	**tab;

	tab = NULL;
	tab = ft_strsplit(line, ' ');
	if (ft_strequ(tab[0], "sphere"))
		sphere_init(p, n, tab[1]);
	/*if (ft_strequ(tab[0], "cylinder"))
		cylinder(p, n);*/
	if (ft_strequ(tab[0], "cone"))
		cone_init(p, n, tab[1]);
	/*if (ft_strequ(tab[0], "plane"))
		plane(p, n);*/
	if (ft_strequ(tab[0], "camera"))
		camera(p, tab);
	if (ft_strequ(tab[0], "light"))
		set_light(p, tab);
	if (ft_strequ(tab[0], "ambient"))
		p->ambient = strtod(tab[1], NULL);
    free_tab(tab);
	return (0);
}

int		read_file(t_data *p, char *file)
{
	char	*line;
	int		i;
	int		n; //номер объекта

	i = 0;
	p->obj_n = object_num(file);
	p->figur = NULL;
	n = -1;
	if (!p->obj_n)
	{
		ft_putstr("File is invalid: no objects found\n");
		return (-1);
	}
	if (!(p->obj = (t_obj*)malloc(sizeof(t_obj) * (p->obj_n + 1))))
	{
		ft_putstr("Memory allocation error\n");
		return (-1);
	}
	p->obj[p->obj_n].type = 5;
	if ((p->fd = open(file, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(p->fd, &line)) > 0)
	{
		create_obj(p, line, &n);
		free(line);
	}
	init(p);
	close(p->fd);
	render(p);
	drow(p);
	free(p->obj);
	return (0);
}
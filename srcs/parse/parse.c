/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:22:19 by mgalt             #+#    #+#             */
/*   Updated: 2020/07/07 20:22:30 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
}

void	parse_sphere(t_data *p, char **s, int obj_n)
{
	char	**coord;
	//int		i;

	coord = ft_strsplit(s[1], ',');
	ft_putstr("4\n");
	p->obj[obj_n].x = ft_atoi(coord[0]);
	ft_putstr("5\n");
	p->obj[obj_n].y = ft_atoi(coord[1]);
	p->obj[obj_n].z = ft_atoi(coord[2]);
	p->obj[obj_n].r = (double)ft_atoi(coord[3]);
	p->obj[obj_n].color = ft_atoi(coord[4]);
	printf("%d\n", p->obj[obj_n].x);
	printf("%d\n", p->obj[obj_n].y);
	printf("%d\n", p->obj[obj_n].z);
	printf("%f\n", p->obj[obj_n].r);
	printf("%d\n", p->obj[obj_n].color);
	free(coord);
	render(p, &(p->obj[obj_n]));
	drow(p);
}

int    parse(char **tab, t_data *p)
{
	int		i;
	char	**line;

	i = 0;
	ft_putstr("1\n");
	line = ft_strsplit(tab[0], ' ');
	ft_putstr("2\n");
	p->obj = (t_obj*)malloc(sizeof(t_obj) * p->obj_n);
	printf("%s\n", line[0]);
	if ((ft_strcmp(line[0], "sphere")) == 0)
	{
		ft_putstr("3\n");
		p->obj[i].type = "sphere";
		i++;
		parse_sphere(p, line, i);
	}

	return (0);
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
		//free(line);
	}
	close(fd);
	return (n);
}

/*void	parse_figure(t_data *p, char *line)
{
	//if (p && line)
	//	line = NULL;
	char	**tab;
	char	**tab1;
	int		i;

	tab = NULL;
	tab = ft_strsplit(line, ' ');
	tab1 = ft_strsplit(tab[1], ',');
	i = 0;
	
}*/

void	parse_obj(t_obj *obj, char **tab)
{
	t_vector	v;

	vector_data()
	
}

void	parse_figure(t_data *p, char **tab)
{
	t_obj	obj;
	t_obj	*obj1;
	int		i;

	i = 0;
	parse_obj(&obj, tab);
	
}

void	check_line(t_data *p, char **tab)
{
	if (!(ft_strcmp(tab[0], "sphere")) || !(ft_strcmp(tab[0], "cone")) ||
	!(ft_strcmp(tab[0], "cylinder")) || !(ft_strcmp(tab[0], "plane")))
		parse_figure(p, tab);
	if (!(ft_strcmp(tab[0], "camera")))
		camera();
	if (!(ft_strcmp(tab[0], "light")))
		hfgh();
	if (!(ft_strcmp(tab[0], "ambient")))
		ambient();
}

int		read_file(t_data *p, char *file)
{
	char	*line;
	char	**tab;
	int		i;
	//int		obj_n;

	i = 0;
	p->obj_n = 0;
	p->obj_n = object_num(file);
	if (!p->obj_n)
	{
		ft_putstr("File is invalid\n");
		return (-1);
	}
	printf("Obj_num: %d\n", p->obj_n);
	if (!(p->fd = open(file, O_RDONLY)))
		return (-1);
	//tab = (char**)malloc(sizeof(char*) * 10);
	while ((get_next_line(p->fd, &line)) > 0)
	{
		tab = ft_strsplit(line, ' ');	
		//tab[i] = line;
		printf("%s\n", tab[i]);
		//free(line);
		i++;
		check_line(p, tab);
		free_tab(tab);
		free(line);
	}
	p->line_nbr = i;
	parse(tab, p);
	close(p->fd);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 18:06:23 by mgalt             #+#    #+#             */
/*   Updated: 2020/07/11 18:45:05 by mgalt            ###   ########.fr       */
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


int		create_obj(t_data *p, char *line, int *n)
{
	char	**tab;

	tab = NULL;
	tab = ft_strsplit(line, ' ');
	if (ft_strequ(tab[0], "sphere"))
		sphere_init(p, n, tab[1]);
	/*if (ft_strequ(tab[0], "cylinder"))
		cylinder(p, n);
	if (ft_strequ(tab[0], "cone"))
		cone(p, n);
	if (ft_strequ(tab[0], "plane"))
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
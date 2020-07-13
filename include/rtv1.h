/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:23:19 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/13 16:02:03 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RTV1_H

# define RTV1_H

# include <math.h>
# include "libft.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# define SPHERE 1
# define CYLINDRE 2
# define CONE 3
# define PLANE 4
# define LIGHT 5
# define CAMERA 6
# define	WIN_SIZE_X	1024
# define	WIN_SIZE_Y	960

typedef struct		s_obj
{
	int				x;
	int				y;
	int				z;
	double			r;
	int				color;
	int				type;
}					t_obj;

typedef struct 		s_cone
{
	int				x;
	int				y;
	int				z;
	double			r;
	int				vx;
	int				vy;
	int				vz;
	double			specular;
	int				color;
	struct s_cone	*next;
}					t_cone;

typedef struct		s_orb
{
	int				x;
	int				y;
	int				z;
	double			r;
	double			specular;
	int				color;
	int				type;
	struct s_orb	*next;
}					t_orb;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_camera
{
	double			x;
	double			y;
	double			z;
	int				canv_h;
	int				canv_w;
	int				canv_d;
}					t_camera;

typedef struct		s_img
{
	void			*img;
	int				bit_per_pixel;
	int				size_line;
	int				endline;
	int				*img_data;
}					t_img;

typedef struct		s_mlx
{
	void			*win;
	void			*mlx;
}					t_mlx;

typedef struct		s_data
{
	t_img			img;
	t_mlx			mlx;
	t_img			canv;
	t_camera		camera;
	t_obj			*obj;
	t_vector		l_p;
	t_vector		l_d;
	t_list			*figur;
	double			intens_p;
	double			intens_d;
	int				obj_n;
	int				fd;
	int				line_nbr;
	double			ambient;
	double			specular;
}					t_data;

////init------------------------------------------
int					camera_init(t_data *p);
int					init(t_data *p);
void				init_mlx(t_data *p);
////init figures----------------------------------
t_orb				orb_init(int x, int y, int z, int r, int color, double spec, int type);
t_orb				*orb_clon(const t_list *o);
t_orb				*new_orb(t_orb new);
////render----------------------------------------
int					render(t_data *p);
int					ray_tracing(t_data *p, t_vector r, t_orb *o, double *t);
int					drow(t_data *p);
////vector---------------------------------------
t_vector			vec_mult_cst(t_vector a, double t);
t_vector			vec_diff(t_vector a, t_vector b);
t_vector			vec_sum(t_vector a, t_vector b);
t_vector			new_vec(double x, double y, double z);
t_vector			vec_scal_mult(t_vector a, t_vector b);
double				vec_dot(t_vector a, t_vector b);
double				vec_length(t_vector a);
t_vector			vec_divis_cst(t_vector a, double t);
t_vector			rev_vec(t_vector a);
////light-----------------------------------------
double				light_ambient();
double				light_point(t_vector p, t_vector n, t_vector v, double s, t_data *q);
double				light_direction(t_vector n, t_vector v, double s, t_data *q);
double				light_intens(t_vector p, t_vector n, t_vector v, double s, t_data *q);
int					color(int color, double i);
int					get_color(double t, t_data *q, t_vector d, t_orb *o);
////error-----------------------------------------
void				usage(int cod);
void				error(int cod);
void				error_log(int cod);

////keys------------------------------------------
int					key_press(int key, t_data *p);
int					escape(void);
////parsing---------------------------------------
int					create_obj(t_data *p, char *line, int *n);
int					read_file(t_data *p, char *file);
int					object_num(char *file);
int					len_tab(char **tab);
void				free_tab(char **tab);
int					set_light(t_data *p, char **tab);
int					camera(t_data *p, char **tab);
int					sphere_init(t_data *p, int *n, char *line);
////keys------------------------------------------
int					key_press(int key, t_data *p);
int					escape(void);
double	min(double a, double b);
int					len_tab(char **tab);

#endif
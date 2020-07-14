/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:23:19 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/14 16:53:53 by mgalt            ###   ########.fr       */
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
# define RED 16711680
# define GREEN 65280
# define BLUE 255
# define YELLOW 16776960
# define WIN_SIZE_X	1024
# define WIN_SIZE_Y	960

typedef struct		s_obj
{
	int				x;
	int				y;
	int				z;
	double			r;
	int				color;
	int				type;
}					t_obj;

typedef	struct		s_t
{
	double			t_min;
	double			t_max;
}					t_t;

typedef struct		s_light
{
	double			x;
	double			y;
	double			z;
	double			intens;
}					t_light;

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

typedef struct		s_3_vec
{
	t_vector		p;
	t_vector		n;
	t_vector		v;

}					t_3_vec;

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

typedef struct 		s_l
{
	t_vector		l_d;
	double			intens_p;
	double			intens_d;
	double			ambient;
	double			specular;
	int				shadows;
}					t_l;


typedef struct		s_data
{
	t_img			img;
	t_mlx			mlx;
	t_img			canv;
	t_camera		camera;
	t_obj			*obj;
	t_list			*figur;
	t_list			*light;
	t_l				l;
	int				obj_n;
	int				fd;
	int				line_nbr;
}					t_data;

////init------------------------------------------
int					camera_init(t_data *p);
int					init(t_data *p);
void				init_mlx(t_data *p);
////init figures----------------------------------
t_orb				orb_init(int x, int y, int z, int r, char *color, double spec, int type);
t_orb				orb_clon(const t_list *o);
t_orb				*new_orb(t_orb new);
////render----------------------------------------
int					render(t_data *p);
int					ray_tracing(t_data *p, t_vector r, t_orb *o, t_t *t);
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
t_3_vec				new_vec_3(t_vector a, t_vector b, t_vector c);
////light-----------------------------------------
double				light_ambient();
double				light_point(t_data *p, t_3_vec tre, t_light *light, double s);
double				light_direction(t_data *p, t_3_vec tre, double s);
double				light_intens(t_data *p ,t_3_vec tre, double s);
t_light				light_clon(const t_list	*light);
double				spec(t_vector l, t_3_vec tre, double s, double i);
int					shadow_ray_tracing(t_3_vec q, t_orb *o, t_t *t);
int					shadow_render_cy(t_data *p, t_3_vec r, t_t *t);
//double				light_point(t_vector p, t_vector n, t_vector v, double s, t_data *q);
//double				light_direction(t_vector n, t_vector v, double s, t_data *q);
//double				light_intens(t_vector p, t_vector n, t_vector v, double s, t_data *q);
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

double				min(double a, double b, t_t *t);
int					len_tab(char **tab);
double  			ft_strtodbl(char *s);

#endif
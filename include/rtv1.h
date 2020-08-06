/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:23:19 by wpoudre           #+#    #+#             */
/*   Updated: 2020/08/06 21:25:04 by mgalt            ###   ########.fr       */
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
# include <pthread.h>
# define SPHERE 1
# define CYLINDER 2
# define CONE 3
# define PLANE 4
# define LIGHT 5
# define CAMERA 6
# define RED 16711680
# define GREEN 65280
# define BLUE 2831278
# define YELLOW 15131741 //16776960
# define AQUA 61680
# define GRAY 6447965 //5790037
# define GREY 9539985
# define GREY1 7829367
# define WIN_SIZE_X	960
# define WIN_SIZE_Y	960
# define NO_CAMERA 7
# define USAGE 8
# define NO_OBJECTS 9
# define PARAMETERS 10
# define NO_FD 11
//# define THREADS 32
//# define THREAD_WIDTH 32

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

typedef struct		s_disk
{
	t_vector 		v_min_vdotva;
	double			v_min_vdotva_sqr;
	t_vector 		delta_p;
	double			delta_p_sqr;
	double			cos_a_sqr;
	double			sin_a_sqr;
	double			dot_oc_v;
}					t_disk;

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

typedef struct		s_obj
{
	t_vector		c;
	t_vector		v;
	double			a;
	double			r;
	double			specular;
	int				color;
	int				type;
}					t_obj;

typedef struct		s_plane
{
	int				x;
	int				y;
	int				z;
	int				d;
	t_vector		n;
	int				color;
	int				type;
	struct s_plane	*next;	
}					t_plane;

typedef struct		s_camera
{
	double			x;
	double			y;
	double			z;
	int				canv_h;
	int				canv_w;
	int				canv_d;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	int				cam;
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
	double			intens;
	int				is_dir;
}					t_l;

typedef struct		s_res
{
	t_vector		d;
	t_obj			o;
	double			t;
}					t_res;

typedef struct		s_qn
{
	double			w;
	double			x;
	double			y;
	double			z;
}					t_qn;

typedef struct		s_data
{
	t_img			img;
	t_mlx			mlx;
	t_img			canv;
	t_camera		camera;
	t_list			*figur;
	t_list			*light;	
	t_qn			rot;
	t_l				l;
	double			ambient;
	int				x;
	int				y;
	int				max_x;
	int				max_y;
	int				obj_n;
	int				fd;
	int				line_nbr;
}					t_data;

////init------------------------------------------
int					camera_init(t_data *p);
int					init(t_data *p);
void				init_mlx(t_data *p);
////init figures----------------------------------
t_obj				obj_init1(t_vector c, t_vector v, double a, double r);
t_obj				obj_init2(t_obj obj, double specular, char *color, int type);
t_obj				obj_clon(const t_list *o);
t_obj				*new_obj(t_obj new);
int					figur_init(t_data *p, char *type, char *line);
////render----------------------------------------
int					render(t_data *p);
void				render_cy(t_data *p, t_vector r, int j);
t_res				ray_tracing(t_data *p, t_vector r, t_obj *o, t_t *t);
int					drow(t_data *p);
///rot -----------------------
t_qn				qn_min(t_qn s);
t_qn				qn_sum(t_qn q1, t_qn q2);
void				magn(t_qn *st);
void				qn_rot(t_data *p, t_qn qn, double agl);
t_qn				rotate_e(t_qn vec, t_data *p);
void				rot(t_vector *p1, t_data *p);
void				rotation(t_data *p);
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
double				spec(t_vector l, t_3_vec tre, double s, double i);
int					color(int color, double i);
int					get_color(double t, t_data *q, t_vector d, t_obj *o);
t_light				light_clon(const t_list	*light);
double				spec(t_vector l, t_3_vec tre, double s, double i);
int					shadow_ray_tracing(t_3_vec q, t_obj *o, t_t *t);
int					shadow_render_cy(t_data *p, t_3_vec r, t_t *t);
void				ambience(t_data *p, char *s);
////error-----------------------------------------
void				usage(int cod);
void				error(int cod);
void				error_log(int cod);
int					error_output(int err);
////disc------------------------------------------
double				*disk_sphere(t_vector d, t_vector oc, t_obj *figur, double *t);
double				*disk_cone(t_vector d, t_vector oc, t_obj *figur, double *t);
double				*f_disk(t_vector d, t_vector oc, t_obj *figur, double *t);
////norm------------------------------------------
t_vector			norm_sphere(t_obj *fig, t_vector p);
t_vector			norm_cone(t_vector oc, double t, t_vector d, t_vector p, t_obj *fig);
t_vector			normals(t_data *q, t_obj *fig, t_vector p, t_vector d, double t);
////keys------------------------------------------
int					key_press(int key, t_data *p);
int					escape(void);
////parsing---------------------------------------
int					create_obj(t_data *p, char *line);
int					read_file(t_data *p, char *file);
int					object_num(char *file);
int					len_tab(char **tab);
void				free_tab(char **tab);
int					set_light(t_data *p, char **tab);
int					camera(t_data *p, char **tab);
int					sphere_init(t_data *p, int *n, char *line);

double				min(double a, double b);
double				max(double a, double b);
int					len_tab(char **tab);
double  			ft_strtodbl(char *s);
void				create_thread(t_data *p);
int 				get_color_pl(double t, t_data *q, t_vector d, t_vector l0, t_plane *o);
t_plane				plane_clon(const t_list *o);

#endif
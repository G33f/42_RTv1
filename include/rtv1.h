/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:23:19 by wpoudre           #+#    #+#             */
/*   Updated: 2020/07/03 15:23:22 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H

# define RTV1_H

# include <math.h>
#include <stdio.h>
# include "libft.h"
# include "mlx.h"

# define	WIN_SIZE_X	960
# define	WIN_SIZE_Y	960



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

typedef struct		s_orb
{
	int				x;
	int				y;
	int				z;
	double			r;
	double			specular;
	int				color;
	struct s_orb	*next;
}					t_orb;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_res
{
	t_orb			o;
	t_vector		d;
	double			t;
}					t_res;

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

typedef struct		s_data
{
	t_img			img;
	t_mlx			mlx;
	t_img			canv;
	t_camera		camera;
	t_list			*figur;
	t_list			*light;
}					t_data;

////init------------------------------------------
int					camera_init(t_data *p);
int					init(t_data *p);
void				init_mlx(t_data *p);
t_orb				*new_orb(t_orb new);
void				figur_init(t_data *p);
////init figures and light------------------------
t_orb				orb_init(int x, int y, int z, int r, int color, double spec);
t_orb				orb_clon(const t_list *o);
t_light				light_init(	double x, double y, double z, double intens);
////render----------------------------------------
int					render(t_data *p);
void				render_cy(t_data *p, t_vector r, int j);
int					ray_tracing(t_data *p, t_vector r, t_orb *o, t_t *t);
int					drow(t_data *p);
////vector---------------------------------------
t_vector			vec_mult_cst(t_vector a, double t);
t_vector			vec_diff(t_vector a, t_vector b);
t_vector			vec_sum(t_vector a, t_vector b);
t_vector			new_vec(double x, double y, double z);
t_vector			vec_scal_mult(t_vector a, t_vector b);
t_vector			rev_vec(t_vector a);
double				vec_dot(t_vector a, t_vector b);
double				vec_length(t_vector a);
t_vector			vec_divis_cst(t_vector a, double t);
t_3_vec				vec_3_init(t_vector p, t_vector n, t_vector v);
t_3_vec 			new_vec_3(t_vector a, t_vector b, t_vector c);
////light-----------------------------------------
double				light_ambient();
double				light_point(t_data *p, t_3_vec tre, t_light *light, double s);
double				light_direction(t_data *p, t_3_vec tre, double s);
double				light_intens(t_data *p ,t_3_vec tre, double s);
int					color(int color, double i);
int					get_color(double t, t_data *q, t_vector d, t_orb *o);
t_light				light_clon(const t_list	*light);
double				spec(t_vector l, t_3_vec tre, double s, double i);
int					shadow_ray_tracing(t_3_vec q, t_orb *o, t_t *t);
int					shadow_render_cy(t_data *p, t_3_vec r, t_t *t);
double				min(double a, double b, t_t *t);
////error-----------------------------------------
void				usage(int cod);
void				error(int cod);
void				error_log(int cod);
////testing---------------------------------------
void				test(t_data *p);
void 				print_vec(t_vector v);
t_vector			rev_vec(t_vector a);
#endif

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 10:34:56 by wpoudre           #+#    #+#              #
#    Updated: 2020/07/16 19:35:15 by mgalt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	RTv1

SOURSE_DIRS		:=	srcs srcs/error \
 					srcs/init \
 					srcs/main \
 					srcs/render \
 					srcs/vectors \
 					srcs/light \
 					srcs/parser \
 					srcs/utils \
 					srcs/figur \
 					srcs/rotation \

SRC				:=	srcs/error/error.c \
                  	srcs/init/camera_init.c \
                  	srcs/init/init.c \
                  	srcs/main/main.c \
                  	srcs/render/drow.c \
                  	srcs/render/reander.c \
                  	srcs/vectors/vec_multiply.c \
                  	srcs/vectors/vector_sec.c \
                  	srcs/vectors/vectors.c \
                  	srcs/light/color.c \
                  	srcs/light/light.c \
                  	srcs/light/shadow_and_specular.c \
                  	srcs/parser/camera.c \
                  	srcs/parser/read_file.c \
                  	srcs/parser/set_lights.c \
                  	srcs/utils/utils.c \
                  	srcs/figur/disc.c \
                  	srcs/figur/norm.c \
                  	srcs/rotation/qneon.c \
                  	srcs/rotation/rotate.c \

FLAGS			=	-Wall -Werror -Wextra -O2

framework		=	-L minilibx_macos -lmlx -framework OpenCL -framework OpenGL -framework AppKit -L ./libft -lft -O2

OBJECTS			=	$(notdir $(patsubst %.c,%.o, $(wildcard $(SRC))))

LIB_DIR			=	./libft/

LIB_OBJS		=	$(addprefix $(LIB_DIR), $(LIB_OBJ))

LIB_OBJ			=	*.o

RT_INC			=	include/rtv1.h

LIB_INC			=	include/libft.h

LIB_FILE		=	libft/libft.a

LIB_MLX_FILE	=	minilibx_macos/libmlx.a


all: $(NAME)

$(NAME): $(LIB_FILE) $(LIB_MLX_FILE) $(OBJECTS)
	gcc $(OBJECTS) -o $@ $(framework)

$(LIB_MLX_FILE):
	make -C minilibx_macos

VPATH := $(SOURSE_DIRS)

%.o: %.c $(RT_INC) Makefile
	gcc $(FLAGS) -c $< -I include/

$(LIB_FILE): libfilecheck

libfilecheck:
	@make -C $(LIB_DIR)

clean:
	make clean -C libft
	make clean -C minilibx_macos
	rm -rf *.o

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libbfilecheck
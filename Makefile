# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 10:34:56 by wpoudre           #+#    #+#              #
#    Updated: 2020/01/27 10:35:01 by wpoudre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= RTv1

SOURSE_DIRS		:= srcs srcs/error srcs/init srcs/main srcs/render srcs/vectors

FLAGS			= -Wall -Werror -Wextra

framework		= -L minilibx -lmlx -framework OpenCL -framework OpenGL -framework AppKit -L libft -lft

SEARCH_WILDCARDS:= $(addsuffix /*.c, $(SOURSE_DIRS))

OBJECTS			= $(notdir $(patsubst %.c,%.o, $(wildcard $(SEARCH_WILDCARDS))))

LIB_DIR			= ./libft/

LIB_OBJS		= $(addprefix $(LIB_DIR), $(LIB_OBJ))

LIB_OBJ			= *.o

RT_INC			= include/rtv1.h

LIB_INC			= include/libft.h

all: $(NAME)

$(NAME): $(LIB_OBJS) $(OBJECTS)
	gcc $(OBJECTS) -o $@ $(framework)

VPATH := $(SOURSE_DIRS)

$(LIB_DIR)%.o: $(LIB_DIR)%.c $(LIB_INC)
	make -C $(LIB_DIR)

%.o: %.c $(RT_INC)
	gcc $(FLAGS) -c $< -I include/

clean:
	make clean -C libft
	rm -rf *.o

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

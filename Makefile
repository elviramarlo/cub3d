# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 01:41:10 by elvmarti          #+#    #+#              #
#    Updated: 2022/06/02 17:24:17 by elvmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DAY	= $(shell date +'%d/%m/%Y %H:%M')

NAME = cub3D

HEADER = ./includes/cub.h

SRCS = ./srcs/main.c \
		./srcs/parse_elements.c \
		./srcs/parse_north.c \
		./srcs/parse_south.c \
		./srcs/parse_west.c \
		./srcs/parse_east.c \
		./srcs/parse_resolution.c \
		./srcs/parse_floor.c \
		./srcs/parse_ceiling.c \
		./srcs/print_error.c \
		./srcs/rgb.c \
		./srcs/parse_map.c \
		./srcs/check_matrix.c \
		./srcs/iter_list.c \
		./srcs/cub.c \
		./srcs/events.c \
		./srcs/raycasting.c \
		./srcs/pixel_color.c \
		./srcs/keys.c \
		./srcs/draw.c

SRCS_BONUS = ./bonus/main_bonus.c \
		./bonus/parse_elements_bonus.c \
		./bonus/parse_north_bonus.c \
		./bonus/parse_south_bonus.c \
		./bonus/parse_west_bonus.c \
		./bonus/parse_east_bonus.c \
		./bonus/parse_resolution_bonus.c \
		./bonus/parse_floor_bonus.c \
		./bonus/parse_ceiling_bonus.c \
		./bonus/texture_door_bonus.c \
		./bonus/print_error_bonus.c \
		./bonus/rgb_bonus.c \
		./bonus/parse_map_bonus.c \
		./bonus/check_matrix_bonus.c \
		./bonus/iter_list_bonus.c \
		./bonus/cub_bonus.c \
		./bonus/events_bonus.c \
		./bonus/raycasting_bonus.c \
		./bonus/pixel_color_bonus.c \
		./bonus/keys_bonus.c \
		./bonus/draw_bonus.c \
		./bonus/key_space_bonus.c \
		./bonus/minimap_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -O3#-g3 -fsanitize=address

MLXFLAGS = libmlx.dylib -framework Metal -framework AppKit

RM = rm -f

MLX = ./mlx/

MLXNAME = libmlx.dylib

MINILIBX = $(MLX)$(MLXNAME)

LIBFTPATH = ./libft/

LIBFTNAME = libft.a

LIBFT = $(LIBFTPATH)$(LIBFTNAME)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
		@echo $(PURPLE)Compiling ... $(RESET)
		$(CC) ${CFLAGS} ${OBJS} -I -L. ${LIBFT} ${MLXFLAGS} $(MLXNAME) -o ${NAME}

$(MINILIBX):
		@echo $(PURPLE)Make minilibx ... $(RESET)
		make -C $(MLX)
		cp $(MINILIBX) .

$(LIBFT):		
		@echo $(PURPLE)Make libft ... $(RESET)
		make re -C $(LIBFTPATH)

all: $(NAME)

bonus: $(OBJS_BONUS) $(LIBFT) $(MINILIBX)
		@echo $(PURPLE)Compiling ... $(RESET)
		$(CC) ${CFLAGS} ${OBJS_BONUS} -I -L. ${LIBFT} ${MLXFLAGS} $(MLXNAME) -o ${NAME}

clean:
		@echo $(PURPLE)Cleaning ... $(RED)
		$(RM) $(OBJS) $(OBJS_BONUS) $(LIBFTPATH)*.o $(MLX)*.o

fclean: clean
		$(RM) $(NAME) $(LIBFT) $(MLXNAME) $(MINILIBX)

re: fclean all

#Colors
BLACK		:="\033[0;30m"
RED			:="\033[0;31m"
GREEN		:="\033[0;32m"
BROWN		:="\033[0;33m"
BLUE		:="\033[0;34m"
PURPLE		:="\033[0;35m"
CYAN		:="\033[0;36m"
LIGHT_GRAY	:="\033[0;37m"
DARK_GRAY	:="\033[1;30m"
LIGHT_RED	:="\033[1;31m"
LIGHT_GREEN	:="\033[1;32m"
YELLOW		:="\033[1;33m"
LIGHT_BLUE	:="\033[1;34m"
LIGHT_PURPLE:="\033[1;35m"
LIGHT_CYAN	:="\033[1;36m"
WHITE		:="\033[1;37m"
RESET		:="\x1b[0m"
						
.PHONY: all clean fclean bonus re

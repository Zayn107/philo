# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalissa <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 18:06:58 by aalissa           #+#    #+#              #
#    Updated: 2024/08/10 18:15:12 by aalissa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	cc

CFLAGS		=	-Werror -Wall -Wextra -g -pthread -fsanitize=thread

SRCS		=	main.c \
				data_init.c \
			      	get_set.c \
				parsing.c \
				safe_funcs.c \
				utils.c \
				dinner.c \
				monitor.c \
				sync.c \
				write_status.c\

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all

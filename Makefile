# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 12:18:28 by ryhara            #+#    #+#              #
#    Updated: 2023/09/21 22:47:41 by ryhara           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCDIR = ./srcs/
SRC = check_args.c \
		init.c \
		main.c \
		monitoring.c \
		philo_action.c \
		philo.c \
		print.c \
		time.c \

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(SRC:%.c=%.o))
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread
INC = -I ./includes/

ifdef WITH_THREAD
	CFLAGS += -g -fsanitize=thread  -fno-omit-frame-pointer
endif

ifdef WITH_DEBUG
	CFLAGS += -g -fsanitize=address -fno-omit-frame-pointer
endif

all : $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

clean :
	$(RM) $(OBJDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

thread : fclean
	make WITH_THREAD=1

debug : fclean
	make WITH_DEBUG=1

.PHONY : all clean fclean re
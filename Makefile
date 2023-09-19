# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 12:18:28 by ryhara            #+#    #+#              #
#    Updated: 2023/09/19 12:27:10 by ryhara           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCDIR = ./srcs/
SRC =   main.c \

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(SRC:%.c=%.o))
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
INC = -I ./includes/

all : $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

clean :
	$(RM) $(OBJDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
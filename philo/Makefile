# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: foctavia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 12:06:30 by foctavia          #+#    #+#              #
#    Updated: 2022/07/21 12:06:48 by foctavia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = "\033[1;31m"
GREEN = "\033[1;32m"
RESET = "\033[m"

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g3

INCLUDE = -I include/

RM = rm -rf

SRCDIR = src/
OBJDIR = obj/

SRC = philo.c \
		arg.c create.c init.c \
		simulation.c monitor.c \
		error.c end.c\
		utils1.c utils2.c

# BONUS = 

P_SRC = $(addprefix $(SRCDIR), $(SRC))
# B_SRC = $(addprefix $(SRCDIR), $(BONUS))
P_OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))
# B_OBJ = $(addprefix $(OBJDIR), $(BONUS:.c=.o))

all: $(NAME)

$(OBJDIR)%.o : $(SRCDIR)%.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(P_OBJ)
		@echo -n "Compiling philo"
		@$(CC) $(CFLAGS) $(INCLUDE) $(P_OBJ) -o $@
		@echo $(GREEN)"\t\tOK"$(RESET)

# bonus: $(B_OBJ)
# 		$(CC) $(CFLAGS) $(INCLUDE) $(B_OBJ) -o $(NAME)
# 		@echo -n "Compiling bonus"
# 		@echo $(GREEN)"\t\tOK"$(RESET)

clean:
		@$(RM) $(OBJDIR)

fclean: clean
		@$(RM) $(NAME)

re: fclean
	make all

.PHONY: all bonus clean fclean re


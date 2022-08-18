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

NAME = philo_bonus

CC = cc

ifeq ($(DMEM),1)
MEM = -fsanitize=address -g
endif

ifeq ($(DTHREAD),1)
THREAD = -fsanitize=thread -g
endif

CFLAGS = -Wall -Wextra -Werror -pthread -g3 

INCLUDE = -I include/

RM = rm -rf

SRCDIR = src/
OBJDIR = obj/

SRC = philo_bonus.c \
		arg_bonus.c init_bonus.c time_bonus.c\
		simulation_bonus.c monitor_bonus.c \
		check_bonus.c error_bonus.c end_bonus.c\
		utils1_bonus.c utils2_bonus.c

P_SRC = $(addprefix $(SRCDIR), $(SRC))
P_OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJDIR)%.o : $(SRCDIR)%.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) $(MEM) $(THREAD) $(INCLUDE) -c $< -o $@

$(NAME) : $(P_OBJ)
		@echo -n "Compiling philo_bonus"
		@$(CC) $(CFLAGS) $(MEM) $(THREAD) $(INCLUDE) $(P_OBJ) -o $@
		@echo $(GREEN)"\t\tOK"$(RESET)

clean:
		@$(RM) $(OBJDIR)

fclean: clean
		@$(RM) $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re


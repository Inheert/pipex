# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 14:27:18 by tclaereb          #+#    #+#              #
#    Updated: 2024/06/07 19:27:47 by tclaereb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_P = pipex

_SRCS = main.c \
		src/utils.c \
		src/forks.c \

SRCS_DIR = .

SRCS = $(addprefix $(SRCS_DIR)/, $(_SRCS))

SRCO = $(SRCS:.c=.o)

MAKE_LIBFT = $(MAKE) -C ./libft
LIBFT = ./libft/libft.a

FLAG = -g3 -Wall -Wextra -Werror
INC = -I ./

all : $(NAME_P)

$(LIBFT):
	$(MAKE_LIBFT)

$(NAME_P) : $(SRCO) | $(LIBFT)
	gcc $(FLAG) -o $(NAME_P) $(SRCO) $(LIBFT)

%.o : %.c
	gcc $(FLAG) -c $< -o $@ $(INC)

clean :
	/bin/rm -f $(SRCO)
	$(MAKE_LIBFT) clean

fclean : clean
	/bin/rm -f $(NAME_P)
	$(MAKE_LIBFT) fclean

re :
	$(MAKE_LIBFT) fclean
	make fclean
	make

.PHONY : all clean fclean re

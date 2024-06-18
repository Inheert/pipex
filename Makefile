# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 14:27:18 by tclaereb          #+#    #+#              #
#    Updated: 2024/06/18 16:42:36 by tclaereb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

_SRCS = main.c \
		src/forks.c \
		src/utils.c \

SRCS_DIR = .

SRCS = $(addprefix $(SRCS_DIR)/, $(_SRCS))

SRCO = $(SRCS:.c=.o)

MAKE_LIBFT = $(MAKE) -C ./libft
LIBFT = ./libft/libft.a

FLAG = -g3 -Wall -Wextra -Werror
INC = -I ./

all : $(NAME)

$(LIBFT):
	$(MAKE_LIBFT)

$(NAME) : $(SRCO) | $(LIBFT)
	cc $(FLAG) -o $(NAME) $(SRCO) $(LIBFT)

%.o : %.c
	cc $(FLAG) -c $< -o $@ $(INC)

clean :
	/bin/rm -f $(SRCO)
	$(MAKE_LIBFT) clean

fclean : clean
	/bin/rm -f $(NAME)
	$(MAKE_LIBFT) fclean

re :
	$(MAKE_LIBFT) fclean
	make fclean
	make

.PHONY : all clean fclean re

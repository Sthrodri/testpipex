# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 14:47:02 by sthrodri          #+#    #+#              #
#    Updated: 2025/01/07 14:53:16 by sthrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  pipex
CC =    cc
CFLAGS =        -Wall -Wextra -Werror
SRC =   pipex.c utils.c libft/libft.a
OBJ =   $(SRC:.c=.o)
RM =    rm -f

all:    $(NAME)

$(NAME):
	make all -C libft
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(NAME)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re:     fclean  all

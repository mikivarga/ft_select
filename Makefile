#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvarga <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/03 18:17:43 by mvarga            #+#    #+#              #
#    Updated: 2017/06/03 19:02:44 by mvarga           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_select

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -ltermcap

SOURCE = ft_cursor_mode.c\
		ft_lst.c\
		ft_draw.c\
		ft_menu.c\
		main.c

OBJECTS = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C ./libft
	@gcc -o $(NAME) $(CFLAGS) $(SOURCE) -I ft_minishell.h ./libft/libft.a $(LFLAGS)

%.o: ./%.c
	@gcc $(CFALGS) -o $@ -c $< -I ft_select.h

clean:
	@make clean -C ./libft
	@ $(RM) $(OBJECTS)

fclean: clean
	@ $(RM) $(OBJ) $(NAME)
	@ make fclean -C ./libft

re: fclean all
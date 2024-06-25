# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbakker <jbakker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2024/06/25 20:36:33 by jbakker       #+#    #+#                  #
#    Updated: 2024/06/25 20:41:27 by jbakker       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = string.a

CC := cc
DIR := objs/
EXTRAFLAGS := -Wall -Wextra -Werror

SRCS := string_init.c string_functions.c

BINS := $(addprefix ${DIR}, ${SRCS:.c=.o})

all: ${NAME}

${NAME}: ${BINS}
	@ar r ${NAME} ${BINS}

${DIR}%.o: %.c string.h
	@mkdir -p ${DIR}
	@${CC} ${EXTRAFLAGS} -c $< -o $@

clean:
	@rm -rf ${DIR}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re ${NAME}
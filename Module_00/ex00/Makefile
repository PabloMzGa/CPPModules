# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablo <pablo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:30 by pabmart2          #+#    #+#              #
#    Updated: 2025/11/18 18:15:00 by pablo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror

NAME = megaphone

SRC = megaphone.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@printf "\033[32m\n¡$(NAME) compiled! \
	ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\033[0m\n"

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@printf "\033[34mCompiling: \033[0m$<\n"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

################################################
.PHONY: all debug debug-asan clean fclean re

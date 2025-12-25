# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablo <pablo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:30 by pabmart2          #+#    #+#              #
#    Updated: 2025/12/25 17:12:53 by pablo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 #-gdwarf-4

BUILD_DIR = build
NAME = $(BUILD_DIR)/materialist

HEADERS = 	AMateria.hpp \
			Character.hpp \
			Cure.hpp \
			Ice.hpp \
			ICharacter.hpp \
			IMateriaSource.hpp \
			MateriaSource.hpp \

SRC =		main.cpp \
			AMateria.cpp \
			Character.cpp \
			Cure.cpp \
			Ice.cpp \
			MateriaSource.cpp \

OBJ_DIR = $(BUILD_DIR)/obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@printf "\033[32m\n¡$(NAME) compiled! \
	ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\033[0m\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@printf "\033[34mCompiling: \033[0m$<\n"

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

################################################
.PHONY: all debug debug-asan clean fclean re

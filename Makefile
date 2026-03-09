NAME = ft_irc

CPP = c++

CPPFLAGS = -g3 -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRCS = $(SRC_DIR)/main.cpp \
	   $(SRC_DIR)/client_class.cpp \
	   $(SRC_DIR)/server_class.cpp \
	   $(SRC_DIR)/parsing.cpp

HEADER = $(INC_DIR)/ft_irc.hpp \
		 $(INC_DIR)/server_class.hpp \
		 $(INC_DIR)/client_class.hpp \
		 $(INC_DIR)/parsing.hpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER) | $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
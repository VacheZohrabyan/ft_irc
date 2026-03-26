NAME = ft_irc

CPP = c++

CPPFLAGS = -g3 -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRCS = $(SRC_DIR)/main.cpp \
	   $(SRC_DIR)/server.cpp \
	   $(SRC_DIR)/client.cpp
	  

HEADER = $(INC_DIR)/ft_irc.hpp \
		 $(INC_DIR)/server.hpp \
		 $(INC_DIR)/client.hpp
		 

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
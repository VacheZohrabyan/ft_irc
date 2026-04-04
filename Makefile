NAME = ft_irc

CPP = c++

CPPFLAGS = -g3 -Wall -Wextra -Werror

SRC_DIR = src

REG_DIR = register
CHA_DIR = channel
ADM_DIR = administration
MES_DIR = message

OBJ_DIR = obj
INC_DIR = inc

SRCS = $(SRC_DIR)/main.cpp \
	   $(SRC_DIR)/server.cpp \
	   $(SRC_DIR)/utils.cpp \
	   $(SRC_DIR)/client.cpp \
	   $(SRC_DIR)/$(REG_DIR)/capCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/passCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/nickCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/userCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/pingCommand.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/chanel.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/joinCommand.cpp \
	  

HEADER = $(INC_DIR)/include.hpp \
		 $(INC_DIR)/server.hpp \
		 $(INC_DIR)/client.hpp \
		 $(INC_DIR)/utils.hpp \
		 $(INC_DIR)/$(REG_DIR)/ARegisterCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/capCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/passCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/nickCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/userCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/pingCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/AChannelCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/chanel.hpp \
		 $(INC_DIR)/$(CHA_DIR)/joinCommand.hpp \


OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

INCLUDES    = -I$(INC_DIR) -I$(INC_DIR)/register -I$(INC_DIR)/channel -I$(INC_DIR)/administration -I$(INC_DIR)/message

all: $(NAME)

$(NAME): $(OBJS) 
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -I$(INCLUDES) -c $< -o $@

# $(OBJ_DIR):
# 	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
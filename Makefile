NAME = ft_irc

CPP = c++

CPPFLAGS = -g3 -Wall -Wextra -Werror

SRC_DIR = src

REG_DIR = register
CHA_DIR = channel
ADM_DIR = administration
MES_DIR = message

MODE_DIR = mode
OPER_DIR = operMode

OBJ_DIR = obj
INC_DIR = inc

SRCS = $(SRC_DIR)/main.cpp \
	   $(SRC_DIR)/server.cpp \
	   $(SRC_DIR)/utils.cpp \
	   $(SRC_DIR)/client.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(OPER_DIR)/killMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(OPER_DIR)/rehashMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(OPER_DIR)/restartMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(OPER_DIR)/sQuitMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(OPER_DIR)/wallopsMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/modeCommand.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/whoCommand.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/whoisCommand.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/operCommand.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(MODE_DIR)/inviteMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(MODE_DIR)/keyMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(MODE_DIR)/limitMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(MODE_DIR)/operatorMode.cpp \
	   $(SRC_DIR)/$(ADM_DIR)/$(MODE_DIR)/topicMode.cpp \
	   $(SRC_DIR)/$(REG_DIR)/capCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/passCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/nickCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/userCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/pingCommand.cpp \
	   $(SRC_DIR)/$(REG_DIR)/quitCommand.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/chanel.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/joinCommand.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/quitCommand.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/partCommand.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/namesCommand.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/listCommand.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/inviteCommand.cpp \
	   $(SRC_DIR)/$(CHA_DIR)/kickCommand.cpp \
	   $(SRC_DIR)/$(MES_DIR)/privmsgCommand.cpp \
	   $(SRC_DIR)/$(MES_DIR)/quitCommand.cpp \
	   $(SRC_DIR)/$(MES_DIR)/noticeCommand.cpp \
	  

HEADER = $(INC_DIR)/include.hpp \
		 $(INC_DIR)/server.hpp \
		 $(INC_DIR)/client.hpp \
		 $(INC_DIR)/utils.hpp \
		 $(INC_DIR)/$(ADM_DIR)/$(OPER_DIR)/killMode.hpp \
		 $(INC_DIR)/$(ADM_DIR)/$(OPER_DIR)/rehashMode.hpp \
		 $(INC_DIR)/$(ADM_DIR)/$(OPER_DIR)/restartMode.hpp \
		 $(INC_DIR)/$(ADM_DIR)/$(OPER_DIR)/sQuitMode.hpp \
		 $(INC_DIR)/$(ADM_DIR)/$(OPER_DIR)/wallopsMode.hpp \
		 $(INC_DIR)/$(ADM_DIR)/modeCommand.hpp \
		 $(INC_DIR)/$(ADM_DIR)/whoCommand.hpp \
		 $(INC_DIR)/$(ADM_DIR)/whoisCommand.hpp \
		 $(INC_DIR)/$(ADM_DIR)/operCommand.hpp \
		 $(INC_DIR)/$(ADM_DIR)/$(MODE_DIR)/AModeCommand.hpp \
		 $(INC_DIR)/$(ADM_DIR)/$(MODE_DIR)/inviteMode.hpp \
	     $(INC_DIR)/$(ADM_DIR)/$(MODE_DIR)/keyMode.hpp \
	     $(INC_DIR)/$(ADM_DIR)/$(MODE_DIR)/limitMode.hpp \
	     $(INC_DIR)/$(ADM_DIR)/$(MODE_DIR)/operatorMode.hpp \
	     $(INC_DIR)/$(ADM_DIR)/$(MODE_DIR)/topicMode.hpp \
		 $(INC_DIR)/$(REG_DIR)/ARegisterCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/capCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/passCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/nickCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/userCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/pingCommand.hpp \
		 $(INC_DIR)/$(REG_DIR)/quitCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/AChannelCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/chanel.hpp \
		 $(INC_DIR)/$(CHA_DIR)/joinCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/quitCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/partCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/namesCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/listCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/inviteCommand.hpp \
		 $(INC_DIR)/$(CHA_DIR)/kickCommand.hpp \
	     $(INC_DIR)/$(MES_DIR)/privmsgCommand.hpp \
	     $(INC_DIR)/$(MES_DIR)/noticeCommand.hpp \
	     $(INC_DIR)/$(MES_DIR)/quitCommand.hpp 


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
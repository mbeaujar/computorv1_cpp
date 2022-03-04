NAME		= computor
CXX			= clang++
CXXFLAGS 	= -Wall -Wextra -Werror
RM			= rm -rf

SRCS_DIR	= source
SRCS_FILE	= main.cpp
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_FILE))

OBJS_DIR	= .object
OBJS_FILE	= $(SRCS_FILE:.cpp=.o)
OBJS		= $(addprefix $(OBJS_DIR)/, $(OBJS_FILE))

.SILENT:

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR): 
	mkdir -p $@

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all $(NAME) $(OBJS_DIR) clean fclean re
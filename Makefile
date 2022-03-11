NAME		= computor
CXX			= clang++
CXXFLAGS	= -Wall -Wextra -Werror
RM			= rm -rf
BONUS=0

SRCS_DIR	= source
SRCS_FILE	= main.cpp \
					Solver.cpp \
					Term.cpp \
					Parser.cpp
SRCS		= $(addprefix $(SRCS_DIR)/, $(SRCS_FILE))

OBJS_DIR	= .object
OBJS_FILE	= $(SRCS_FILE:.cpp=.o)
OBJS		= $(addprefix $(OBJS_DIR)/, $(OBJS_FILE))

.SILENT:

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -D BONUS=$(BONUS) -c $< -o $@

$(OBJS_DIR): 
	mkdir -p $@

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@


bonus: BONUS=1
bonus: fclean $(OBJS_DIR) $(OBJS) $(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all $(NAME) $(OBJS_DIR) clean fclean re bonus debug
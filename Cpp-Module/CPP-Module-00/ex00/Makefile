NAME := megaphone

CXX := c++

CXXFLAGES := -Wall -Werror -Wextra -std=c++98

SRCS := megaphone.cpp

OBJS := $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGES) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGES) -c $< -o $@
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re

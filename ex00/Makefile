NAME     = convert
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS     = main.cpp ScalarConverter.cpp DetectType.cpp DisplayTypes.cpp
OBJS     = $(SRCS:.cpp=.o)
HEADERS  = ScalarConverter.hpp DetectType.hpp DisplayTypes.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
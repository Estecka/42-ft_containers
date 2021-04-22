HDRS = \

SRCS = \

OBJS = ${SRCS:.cpp=.o}

NAMES = \

CPPFLAGS = -Wall -Wextra -Werror -std=c++98
CXX=clang++

all: ${NAMES}

${NAMES}: ${OBJS}
	${CXX} -o ${NAME} ${OBJS} ${CPPFLAGS}

${OBJS}: ${HDRS}

# For some reason, the `.test` pre-extension is absolutely needed.
# The rule breaks completely if the files are named `.hpp.cpp` and `.hpp.o`.
headers_test: ${HDRS:.hpp=.hpp.test.o}
${HDRS:.hpp=.hpp.test.cpp}: ${HDRS}
	cp ${@F:.hpp.test.cpp=.hpp} ${@F} ;

clean:
	rm -f *.o
	rm -f *.hpp.cpp
	rm -f *.hpp.test.cpp

fclean: clean
	rm -f *.out

re: fclean all

.PHONY: all clean fclean all \
	header_test \

PROJECT_DIR = ../

PROJECT_HDRS = \
	less.hpp \
	list.hpp \
	list_iterator.hpp \
	map.hpp \
	map_iterator.hpp \
	not_integer.hpp \
	pair.hpp \
	queue.hpp \
	reconstruct.hpp \
	reverse_iterator.hpp \
	stack.hpp \
	swap.hpp \
	vector.hpp \
	vector_iterator.hpp \

PROJECT_SRCS = \


######################


TEST_HDRS = \
	tester.hpp \

HDRS = $(addprefix ${PROJECT_DIR},${PROJECT_HDRS})

OBJS = ${PROJECT_SRCS:.cpp=.o}

CLASSES = \
	vector \
	list \
	stack \
	queue \
	map \

NAMES = \
	${CLASSES:=.ft.out} \
	${CLASSES:=.std.out} \

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -I ${PROJECT_DIR}
CXX=clang++


all: ${NAMES}

%.ft.out:  ${OBJS} ${HDRS} ${TEST_HDRS} main.%.ft.o
	${CXX} ${CPPFLAGS} main.$*.ft.o ${OBJS} -o $@

%.std.out: ${OBJS} ${HDRS} ${TEST_HDRS} main.%.std.o
	${CXX} ${CPPFLAGS} main.$*.std.o ${OBJS} -o $@

${OBJS}: ${HDRS} ${TEST_HDRS}

main.%.ft.o: main.%.cpp ${HDRS} ${TEST_HDRS}
	${CXX} ${CPPFLAGS} main.$*.cpp -c -o $@ -D NS=ft

main.%.std.o: main.%.cpp ${HDRS} ${TEST_HDRS}
	${CXX} ${CPPFLAGS} main.$*.cpp -c -o $@ -D NS=std

# For some reason, the `.test` pre-extension is absolutely needed.
# The rule breaks completely if the files are named `.hpp.cpp` and `.hpp.o`.
headers_test: ${HDRS:.hpp=.hpp.test.o}
${HDRS:.hpp=.hpp.test.cpp}: ${HDRS}
	cp ${@:.hpp.test.cpp=.hpp} ${@} ;

clean:
	rm -f *.o
	rm -f *.hpp.cpp
	rm -f *.hpp.test.cpp

fclean: clean
	rm -f *.out

re: fclean all

.SECONDARY:

.PHONY: all clean fclean all \
	header_test \

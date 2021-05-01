HDRS = \
	dump.hpp \
	vector.hpp \
	vector_iterator.hpp \
	list.hpp \
	list_iterator.hpp \

SRCS = \

OBJS = ${SRCS:.cpp=.o}


CLASSES = \
	vector \
	list \

NAMES = \
	${CLASSES:=.ft.out} \
	${CLASSES:=.std.out} \

CPPFLAGS = -Wall -Wextra -Werror -std=c++98
CXX=clang++

all: ${NAMES}

%.ft.out: ${OBJS} ${HDRS} main.%.ft.o
	${CXX} ${CPPFLAGS} main.$*.ft.o ${OBJS} -o $@

%.std.out: main.%.std.o ${OBJS} ${HDRS}
	${CXX} ${CPPFLAGS} main.$*.std.o ${OBJS} -o $@

${OBJS}: ${HDRS}

main.%.ft.o: main.%.cpp ${HDRS}
	${CXX} ${CPPFLAGS} main.$*.cpp -c -o $@ -D NS=ft

main.%.std.o: main.%.cpp ${HDRS}
	${CXX} ${CPPFLAGS} main.$*.cpp -c -o $@ -D NS=std

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

.SECONDARY:

.PHONY: all clean fclean all \
	header_test \

# "CUnit for Mr.Ando" is CppUnit-x based C langage testing framework
# for Mr.Ando. It provide the C source code for unit testing. 
# Copyright (C) 2004 Toshikazu Ando.
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

CC=gcc
INCLUDE_OBJ = \
	-I TestRunner\
	-I ../Target
	
OBJS = \
	dijkstra.o\
	dijkstra_test.o\
	testRunner.o
OBJS_DEBUG = dijkstra.o main.o
CFLAG_LM = ${CFLAG} -ggdb -Wall
CFLAG_OBJ = ${CFLAG} -ggdb -Wall
OPTION_DEBUG = -g

#
LIB_X = ${LIB}

TEST_EXE = runExe.exe
DEBUG_EXE = debug.exe

#
all: ${TEST_EXE}
#
${TEST_EXE}: ${OBJS}
	${CC} ${CFLAG_LM} ${CFLAG_OBJ} ${INCLUDE_OBJ} -o ${TEST_EXE} ${OBJS} ${LIB_X}
#
${DEBUG_EXE}: ${OBJS}
	${CC} ${OPTION_DEBUG} ${INCLUDE_OBJ} -o ${DEBUG_EXE} ${OBJS}
#
dijkstra.o: ../target/dijkstra.c
	${CC} ${CFLAG_OBJ} ${INCLUDE_OBJ} -c ../target/dijkstra.c
dijkstra_test.o: ./dijkstra_test.c
	${CC} ${CFLAG_OBJ} ${INCLUDE_OBJ} -c dijkstra_test.c
testRunner.o: TestRunner/testRunner.c
	${CC} ${CFLAG_OBJ} ${INCLUDE_OBJ} -c TestRunner/testRunner.c

#
#
clean:
	cmd /c del ${TEST_EXE} ${DEBUG_EXE} ${OBJS} ${OBJS_DEBUG}
#
test: all
	${TEST_EXE}
#
#
debug: ${OBJS}
	${DEBUG_EXE}
#
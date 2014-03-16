#Makefile

CXX=g++
CC=i586-mingw32msvc-cc
CFLAGS=-g -c -std=c++11
LFLAGS=-g -o 
PACKAGECODE=./code/
PACKAGEXML=$(PACKAGECODE)xml/
PACKAGEINTERFACE=./interface/
PACKAGEGUI=./gui/
INCLUDEDIR=-I./lib/SFML-2.1/include/ -I$(PACKAGECODE) -I$(PACKAGEXML) -I$(PACKAGEINTERFACE) -I$(PACKAGEGUI)
LIBSDIR=./lib/SFML-2.1/lib
LIBS=-L$(LIBSDIR)
AUXLIBS=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -pthread

TARGET=main.out
TARGETW=main.exe
SRCFILE=$(PACKAGECODE)attack.cpp $(PACKAGECODE)factory.cpp $(PACKAGECODE)fight.cpp $(PACKAGECODE)fightManager.cpp $(PACKAGECODE)main.cpp $(PACKAGECODE)pokemon.cpp $(PACKAGECODE)sceneManager.cpp $(PACKAGECODE)type.cpp $(PACKAGEGUI)menuFrame.cpp $(PACKAGEGUI)gameFrame.cpp $(PACKAGEGUI)tileMap.cpp $(PACKAGEGUI)statFrame.cpp
OBJFILE=$(SRCFILE:.cpp=.o)

all : $(TARGET) run
win : $(TARGETW) run

$(TARGET): $(OBJFILE)
	@echo "***********************************"
	@echo "> Creating $@"
	@$(CXX) $^ $(LFLAGS) $@ $(LIBS) $(AUXLIBS)
	@echo ""

.cpp.o:
	@reset
	@echo "***********************************"
	@echo "> Generation of $@ from $<"
	@$(CXX) $(CFLAGS) $(INCLUDEDIR) -o $@ $<
	@echo ""

run:
	@echo "***********************************"
	@echo "> Launching $(TARGET)"
	@reset && export LD_LIBRARY_PATH=$(LIBSDIR) && ./$(TARGET)

clean:
	@echo "***********************************"
	@echo "> Cleaning directories"
	@find ./ -type f -name "*.o" -exec rm -rf {} \;
	@find ./ -type f -name "*.swp" -exec rm -rf {} \;

gdb:
	@echo "***********************************"
	@echo "> Launching gdb"
	gdb ./main.out -x ./gdb.txt

val-log:
	@echo "***********************************"
	@echo "> Creating valgrind log file"
	@export LD_LIBRARY_PATH=$(LIBSDIR) && valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=rawmain.log ./$(TARGET)
val-supp:
	@echo "***********************************"
	@echo "> Creating valgrind suppression file"
	@cat ./rawmain.log | ./parse_valgrind_suppressions.sh >> pv.supp

val:
	@echo "***********************************"
	@echo "> Launching valgrind"
	@export LD_LIBRARY_PATH=$(LIBSDIR) && valgrind ./$(TARGET)
#@export LD_LIBRARY_PATH=$(LIBSDIR) && valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./pv.supp --gen-suppressions=all --log-file=rawmain.log ./$(TARGET)

valg:
	@echo "***********************************"
	@echo "> Launching valgrind"
	@export LD_LIBRARY_PATH=$(LIBSDIR) && valgrind --log-file=rawmain.log ./$(TARGET)

$(TARGETW): $(OBJFILE)
	@echo "***********************************"
	@echo "> Creating $@"
	@$(CC) $^ $(LFLAGS) $@ $(LIBS) $(AUXLIBS)
	@echo ""

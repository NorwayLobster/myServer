#INC_DIR:= ./include/net /usr/include/mysql/  ./include/utilities ./include/task ./include/protobuf
SRC_DIR:= .
#LD_LIBRARY_PATH:=/home/cheng/coding/20200224/spellCorrection/server/lib
#LD_LIBRARY_PATH:=/home/cheng/20200224/project/lib
SOURCES:=$(wildcard *.cc)
OBJECTS:=$(patsubst %.cc,%.o,$(SOURCES))
#LIBS:=-lutilities -lmyprotobuf -lnet -ltask -lpthread -lprotobuf -lcrypt -lmysqlclient 
CXXFLAGS:=-g -Wall -std=c++11 
#-I ../../include/net
#CXXFLAGS:=-g -Wall  -std=c++11 $(LIBS) -Wl,-rpath=$(LD_LIBRARY_PATH) -L $(LD_LIBRARY_PATH) $(addprefix -I, $(INC_DIR)) -Wno-deprecated
ELF:=server

$(ELF):$(OBJECTS)
	$(CXX)  $^  -o ./$@  $(CXXFLAGS) 
clean:
	rm -rf $(OBJECTS) 

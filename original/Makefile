#CPPFLAGS = -w -std=c++11 -O3 -I include
#LNKFLAGS1 = -pg -w -std=c++11 -O3 -I include

CPPFLAGS = -std=c++11 -m64 -I include
LNKFLAGS1 = -std=c++11 -m64 -I include
 
COMP = g++

OBJ_DIR = obj

TARGET = ArvoreGeradora.exe

# Obtém automaticamente a lista de todos os arquivos .cpp 
SRCS := $(wildcard src/*.cpp)
SRCS += main.cpp

# Gera a lista de arquivos de objeto correspondentes na pasta obj
OBJ := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(COMP) $(LNKFLAGS1) $(OBJ) -o $@

# Regra para compilar cada arquivo .cpp e colocar o arquivo de objeto na pasta obj
$(OBJ_DIR)/%.o: src/%.cpp main.cpp
	$(COMP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f *.o


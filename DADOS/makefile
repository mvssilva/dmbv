
#FLAGS = -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -g
LIBED_DEPS = $(patsubst %.c,%.o,$(wildcard ./src/*.c)) 

all: main

%.o: %.c %.h
	gcc $(FLAGS) -c -o $@ $< 

libed.a: $(LIBED_DEPS)
	ar -crs libed.a $(LIBED_DEPS)

main: main.c libed.a
	gcc -o main main.c -I src -L . -led -lm

clean:
	rm -f main libed.a  $(LIBED_DEPS)
	
run:
	./main
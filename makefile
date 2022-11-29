CC = g++
CPPFLAGS = -std=c++17 -g -Wall
DEPS = driver.h website.h BST.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

app: driver.o website.o BST.o
	$(CC) -o app driver.o website.o BST.o

.PHONY: clean
clean:
	$(info -- cleaning up! --)
	rm -f *.o
	rm -f app


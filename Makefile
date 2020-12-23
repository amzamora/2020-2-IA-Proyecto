all: build

build:
	g++ src/main.cpp -o MCLP

clean:
	rm -f MCLP

all: build

build:
	g++ src/main.cpp src/MCLP.cpp src/types.cpp -o MCLP

clean:
	rm -f MCLP

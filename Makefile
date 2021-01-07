all: build

build:
	g++ -std=c++17 src/main.cpp src/MCLP.cpp src/types.cpp -o MCLP

parallel:
	g++ -std=c++17 src/main.cpp src/MCLP_parallel.cpp src/types.cpp -o MCLP -ltbb

clean:
	rm -f MCLP

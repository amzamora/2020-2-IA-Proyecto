#include <iostream>
#include <string>
#include <fstream>

#include "types.hpp"
#include "MCLP.hpp"

Parameters parse_parameters(std::string nodes_file_path, std::string demands_file_path, int S, int p);

int main(int argc, char *argv[]) {
	//  Parse arguments
	if (argc != 5) {
		std::cout << "Usage: ./MCLP nodes_file_path demands_file_path s p" << '\n' << '\n';
		throw std::exception();
	}
	std::string nodes_file_path = argv[1];
	std::string demands_file_path = argv[2];
	int S = std::stoi(argv[3]);
	int p = std::stoi(argv[4]);

	// Parse parameters
	Parameters parameters = parse_parameters(nodes_file_path, demands_file_path, S, p);

	// Solve
	Variables best_solution = MCLP(parameters);

	// Print solution
	print_solution(best_solution);
	return 0;
}

Parameters parse_parameters(std::string nodes_file_path, std::string demands_file_path, int S, int p) {
	Parameters parameters;
	parameters.S = S;
	parameters.p = p;

	// Read file of nodes
	std::ifstream nodes_file(nodes_file_path);
	if (!nodes_file.is_open()) {
		std::cout << "Error: Couldn't read nodes file." << '\n' << '\n';
		throw std::exception();
	}

	// Get number of nodes
	int number_of_nodes;
	nodes_file >> number_of_nodes;
	parameters.nodes.reserve(number_of_nodes);

	// Get nodes
	int x, y;
	while (nodes_file >> x >> y) {
		parameters.nodes.push_back(Node(x, y));
	}

	nodes_file.close();

	// Read file of demands
	std::ifstream demands_file(demands_file_path);
	if (!demands_file.is_open()) {
		std::cout << "Error: Couldn't read demands file." << '\n' << '\n';
		throw std::exception();
	}

	// Get demands
	for(auto it = parameters.nodes.begin(); it != parameters.nodes.end(); it++) {
    	demands_file >> (*it).demand;
	}

	return parameters;
}

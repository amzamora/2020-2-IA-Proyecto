#include <cmath>
#include <iostream>

#include "types.hpp"

Variables MCLP_backtracking(Parameters parameters, Variables variables, int i = 0);
float distance(Node a, Node b);
bool is_solution(Parameters parameters, Variables variables);
bool is_safe(Parameters parameters, Variables variables, int i, int val);
Variables adjust_y(Parameters parameters, Variables variables);
void print_solution(Parameters parameters, Variables variables);

Variables MCLP(Parameters parameters) {
	Variables variables(parameters);
	variables.set_x_i_to(3, true);

	return variables;
}

float z(Variables variables) {
	return variables.z();
}

void print_solution(Variables variables) {
	bool variables_used = false;
	for (unsigned int i = 0; i < variables.x.size(); i++) {
		if (variables.x[i].setted) {
			std::cout << "Used node " << i + 1 << "\n";
			variables_used = true;
		}
	}
	if (!variables_used) {
		std::cout << "No facilities opened." << "\n";
	}
	std::cout << "Demand covered was " << z(variables) << "." << "\n";
	std::cout << "\n";
}

// Variables MCLP_backtracking(Parameters parameters, Variables variables, int i) {
// 		// Check if current variables are a solution
//
// 		// Caculate possible best solutions
// 		for (unsigned int val = 0; val < variables) {
//
// 		}
// }
//
// bool is_solution(Parameters parameters, Variables variables) {
//
// }
//
// bool is_safe(Parameters parameters, Variables variables, int i, int val) {
//
// }
//
// float distance(Node a, Node b) {
// 	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
// }

#include <cmath>
#include <iostream>
#include <algorithm>
#include <execution>

#include "types.hpp"

Variables MCLP_backtracking(Variables variables, int i = 0);
void print_solution(Variables variables);

Variables MCLP(Parameters parameters) {
	Variables variables(parameters);
	return MCLP_backtracking(variables);
}

float z(Variables variables) {
	return variables.z();
}

void print_solution(Variables variables) {
	bool variables_used = false;
	for (unsigned int i = 0; i < variables.x.size(); i++) {
		if (variables.x[i].setted && variables.x[i].value) {
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

Variables MCLP_backtracking(Variables variables, int i) {
	// Check if current variables are a solution
	if (variables.is_solution()) {
		return variables;
	}
	else {
		// Calculate possible solutions
		std::vector<Variables> possible_solutions;

		// Value in domain fo x_i
		std::for_each(
			std::execution::par_unseq,
			variables.x[i].domain.begin(),
			variables.x[i].domain.end(),
			[variables, i, &possible_solutions](auto&& val) {
				if (variables.set_x_i_to_valid(i, val)) {
					// Caculate set the value and move to the next variable
					Variables aux = variables;
					aux.set_x_i_to(i, val);
					aux = MCLP_backtracking(aux, i + 1);

					// If a viable solution is found put on possible_solutions
					if (aux.is_solution()) {
					 	possible_solutions.push_back(aux);
					}
				}
			}
		);

		if (possible_solutions.size() > 0) {
			Variables best = possible_solutions[0];
			for (unsigned i = 0; i < possible_solutions.size(); i++) {
				if (z(possible_solutions[i]) > z(best)) {
					best = possible_solutions[i];
				}
			}
			return best;
		}
		// Else backtrack
		return variables;
	}
}

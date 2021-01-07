#include <cmath>
#include <iostream>
#include <algorithm>
#include <execution>
#include <mutex>

#include "types.hpp"

Variables MCLP_backtracking(Variables variables, int i = 0);

Variables MCLP(Parameters parameters) {
	Variables variables(parameters);
	return MCLP_backtracking(variables);
}

std::mutex m;
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
						m.lock();
					 	possible_solutions.push_back(aux);
						m.unlock();
					}
				}
			}
		);

		if (possible_solutions.size() > 0) {
			Variables best = possible_solutions[0];
			for (unsigned i = 0; i < possible_solutions.size(); i++) {
				if (possible_solutions[i].z() > best.z()) {
					best = possible_solutions[i];
				}
			}
			return best;
		}
		// Else backtrack
		return variables;
	}
}

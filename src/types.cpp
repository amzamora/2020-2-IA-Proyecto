#include <cmath>
#include <iostream>
#include "types.hpp"

Variable::Variable() {
	this->setted = false;
	this->domain.push_back(false);
	this->domain.push_back(true);
}

void Variable::set_value(bool value) {
	this->value = value;
	this->setted = true;
}

float distance(Node a, Node b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


Variables::Variables(Parameters parameters) {
	this->parameters = parameters;

	// Initialize x variables
	this->x.resize(parameters.nodes.size(), Variable());

	// Initialize y variables
	this->y.resize(parameters.nodes.size(), false);
}

void Variables::set_x_i_to(int i, bool value) {
	this->x[i].set_value(value);

	if (value) {
		for (unsigned int j = 0; j < this->y.size(); j++) {
			if (distance(this->parameters.nodes[i], this->parameters.nodes[j]) <= this->parameters.S) {
				this->y[j] = true;
			}
		}
	}
}

bool Variables::set_x_i_to_valid(int i, bool value) const {
	// If (variables to instantiate) + (variables = true) can still be equal to p
	int variables_to_instantiate = this->x.size() - 1 - i;
	int variables_equal_true = 0;
	for (unsigned int j = 0; j < i; j++) {
		if (this->x[j].value == true) {
			variables_equal_true++;
		}
	}
	if (value) variables_equal_true++;
	if (variables_equal_true > this->parameters.p) return false;
	else if (variables_to_instantiate + variables_equal_true < this->parameters.p) return false;
	else return true;
}

bool Variables::is_solution() {
	int facilities_opened = 0;
	for (unsigned int i = 0; i < this->x.size(); i++) {
		if  (!this->x[i].setted) return false;
		else if (this->x[i].value) facilities_opened += 1;
	}
	if (facilities_opened != this->parameters.p) {
		std::cout << facilities_opened << '\n';
		std::cout << "This shouldn't happend :/" << "\n";
		return false;
	}
	return true;
}

float Variables::z() {
	float sum = 0.0;
	for (unsigned int j = 0; j < this->y.size(); j++) {
		sum += this->parameters.nodes[j].demand * this->y[j];
	}
	return sum;
}

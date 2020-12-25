#include <cmath>
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

	for (unsigned int j = 0; j < this->y.size(); j++) {
		if (distance(this->parameters.nodes[i], this->parameters.nodes[j]) <= this->parameters.S) {
			this->y[j] = true;
		}
	}
}

float Variables::z() {
	float sum = 0.0;
	for (unsigned int j = 0; j < this->y.size(); j++) {
		sum += this->parameters.nodes[j].demand * this->y[j];
	}
	return sum;
}

#include <cmath>
#include <iostream>
#include <algorithm>
#include "types.hpp"

Variable::Variable(int nodes) {
	this->setted = false;
	for (unsigned int i = 0; i < nodes; i++) {
		this->domain.push_back(i);
	}
}

void Variable::set_value(int value) {
	this->value = value;
	this->setted = true;
}

void Variable::remove_value_from_domain(int value) {
	this->domain.erase(std::remove(this->domain.begin(), this->domain.end(), value), this->domain.end());
}

float distance(Node a, Node b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Variables::Variables(Parameters parameters) {
	this->parameters = parameters;

	// Initialize x variables
	this->x.resize(parameters.p, Variable(parameters.nodes.size()));

	// Initialize y variables
	this->y.resize(parameters.nodes.size(), false);
}

void Variables::set_x_i_to(int i, int value) {
	this->x[i].set_value(value);

	for (unsigned int j = 0; j < this->y.size(); j++) {
		if (distance(this->parameters.nodes[this->x[i].value], this->parameters.nodes[j]) <= this->parameters.S) {
			this->y[j] = true;
		}
	}

	for (unsigned int j = i + 1; j < this->x.size(); j++) {
		this->x[j].remove_value_from_domain(value);
	}
}

bool Variables::set_x_i_to_valid(int i, int value) const {
	return true;
}

bool Variables::is_solution() {
	for (unsigned int i = 0; i < this->x.size(); i++) {
		if  (!this->x[i].setted) return false;
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

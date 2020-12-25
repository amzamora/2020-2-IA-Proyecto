#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

struct Node {
	int x;
	int y;
	int demand;

	Node(int x, int y) : x(x), y(y) {}
};
float distance(Node a, Node b);

struct Parameters {
	std::vector<Node> nodes;
	int S;
	int p;
};

struct Variable {
	bool setted;
	bool value;
	std::vector<bool> domain;
	Variable();
	void set_value(bool value);
};

struct Variables {
	Parameters parameters;
	std::vector<Variable> x;
	std::vector<bool> y;
	Variables(Parameters parameters);
	void set_x_i_to(int i, bool value);
	float z();
};

#endif

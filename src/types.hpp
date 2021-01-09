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
	int value;
	int last_connected_variable;
	std::vector<int> domain;
	Variable(int nodes_size);
	void set_value(int value, int last_connected_variable);
	void remove_value_from_domain(int value);
};

struct Variables {
	Parameters parameters;
	std::vector<Variable> x;
	std::vector<bool> y;
	int comming_back_from;

	Variables(Parameters parameters);
	void set_x_i_to(int i, int value);
	bool set_x_i_to_valid(int i, int value) const;
	bool no_possible_value_for_x_i(int i);
	bool is_solution();
	float z();
};

#endif

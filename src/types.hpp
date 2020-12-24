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

struct Variables {
    std::vector<bool> y;
    std::vector<bool> x;
};

#endif

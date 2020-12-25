#ifndef MCLP_HPP
#define MCLP_HPP

#include "types.hpp"

float z(Variables variables);
float coverage(Parameters parameters, Variables variables);
Variables MCLP(Parameters parameters);
void print_solution(Variables variables);

#endif

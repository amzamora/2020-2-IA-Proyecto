#ifndef MCLP_HPP
#define MCLP_HPP

#include "types.hpp"

float objective_function(Variables variables);
float coverage(Variables variables);
Variables MCLP(Parameters parameters);

#endif

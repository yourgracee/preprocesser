#include "boolize.hpp"

#define COMMA_IF(n) CAT(COMMA_,BOOLIZE(n))
#define COMMA_0 
#define COMMA_1 ,
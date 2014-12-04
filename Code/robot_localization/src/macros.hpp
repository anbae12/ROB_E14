/*
 * macros.hpp
 *
 *  Created on: Aug 30, 2012
 *      Author: jimali
 */

#ifndef MACROS_HPP_
#define MACROS_HPP_

#include <sstream>
#include <iostream>


#define THROW(ostreamExpression) do { int RW__line = __LINE__;           \
    std::stringstream RW__stream;                                           \
    RW__stream << ostreamExpression;                                        \
    std::cerr << ostreamExpression; \
    throw RW__stream.str();                               \
} while (0)

#define WARN(ostreamExpression) do { int RW__line = __LINE__;           \
    std::stringstream RW__stream;                                           \
    RW__stream << ostreamExpression;                                        \
    std::cout << ostreamExpression; \
} while (0)


#endif /* MACROS_HPP_ */

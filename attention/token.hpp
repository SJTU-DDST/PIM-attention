#ifndef __TOKEN_H
#define __TOKEN_H

#include "vector.hpp"

template <typename Type>
class token
{
public:
    vector<Type> vectors[NUM_HEAD];
    token(Type elem = 1)
    {
        for (int i = 0; i < NUM_HEAD; i++)
        {
            vectors[i] = vector<Type>(elem);
        }
    }
    ~token() {}
};

#endif
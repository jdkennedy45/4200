#include "Integer.h"
using CSC1310::Integer;

Integer::Integer(int val)
{
   value = val;
}

Integer::~Integer()
{
}

int Integer::getValue()
{
   return value;
}

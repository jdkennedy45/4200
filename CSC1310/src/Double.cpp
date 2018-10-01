#include "Double.h"
using CSC1310::Double;

Double::Double(double val)
{
   value = val;
}

Double::~Double()
{
}

double Double::getValue()
{
   return value;
}

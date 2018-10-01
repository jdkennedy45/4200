#include "String_.h"
using CSC1310::String;

#include <cstring>   //needed for strlen and strcmp
#include <cstdlib>
#include <sstream>
#include <iostream>

int String::computeHashFunctionByASCIISum()
{
	int hash_function = 0;
	int str_len = length();
	
	for (int i = 0; i < str_len; i++)
	{
		hash_function += (int) charAt(i);
	}
	
	return hash_function;
}

String::String(const char* char_array)
{
   sz = strlen(char_array);
   char* text = new char[sz+1];
   for (int i = 0; i < sz; i++)
   {
      text[i] = char_array[i];
   }
   text[sz] = 0;  //null terminator
   this->text = text;
   
}

String::~String()
{
   delete[] text;
}

//zero-based
char String::charAt(int index)
{
   if (index < 0 || index >= sz) return -1;
   return text[index];
}

char* String::get_c_str()
{
	int sz = strlen(text);
	
   char* char_array = new char[sz+1];
   for (int i = 0; i < sz; i++)
   {
      char_array[i] = text[i];
   }
   char_array[sz] = 0;  //null terminator
   return char_array;
}

std::string String::get_std_str()
{
   char* char_array = get_c_str();
   std::string std_str(char_array);
   delete[] char_array;
   return std_str;
}

int String::length()
{
	return sz;
}

int String::compare(String* other)
{
   return strcmp(text, other->text);
}

void String::displayString()
{
   std::cout << text;
}

int String::find(char delimiter, int start)
{
   if (start >= sz || start < 0) return -1;

   int loc = sz;
   for (int i = start; i < sz; i++)
   {
      if (text[i] == delimiter)
      {
         loc = i;
         break;
      }
   }

   return loc;  //delimiter not found
}

//the substring will use the characters from start to end inclusive
String String::substr(int start, int end)
{
   if (start > end || start < 0) return NULL;
   if (start > sz || end > sz) return NULL;

   int sub_len = end - start + 1;
   char* sub_text = new char[sub_len + 1];

   int count = 0;
   for (int i = start; i <= end; i++)
   {
      sub_text[count] = text[i];
      count++;
   }
   sub_text[count] = 0;

   String sub((const char*) sub_text);
   delete sub_text;
   return sub;
}

int String::a_to_i()
{
   return atoi(text);
}

float String::a_to_f()
{
   return atof(text);
}

String String::i_to_a(int number)
{
   std::stringstream out;
   out << number;
   const char* text = out.str().c_str();
   String str(text);
   return str;
}

String String::f_to_a(float number)
{
   std::stringstream out;
   out << number;
   const char* text = out.str().c_str();
   String str(text);
   return str;
}

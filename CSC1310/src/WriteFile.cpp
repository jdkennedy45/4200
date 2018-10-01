#include "WriteFile.h"
#include <sstream>
using namespace CSC1310;

WriteFile::WriteFile(const char* file_name)
{
   output_file = new ofstream();
   output_file->open(file_name);
   closed = false;
}

WriteFile::~WriteFile()
{
   close();
   delete output_file;
}

void WriteFile::close()
{
   if (!closed)
   {
      output_file->close();
      closed = true;
   }
}

void WriteFile::writeLine(String* line)
{
   if (!closed && line->length() > 0)
   {
	   char* line_c_str = line->get_c_str();
      *output_file << line_c_str << endl;
	  delete[] line_c_str;
   }
}

void WriteFile::entireFile(const char* file_name, char* file_contents, int file_length)
{
	std::ofstream output_file(file_name, std::ofstream::binary);
	output_file.seekp(0);
	output_file.write(file_contents, file_length);
	output_file.close();
}

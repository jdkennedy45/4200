#if !defined ZIPP
#define ZIPP

#include "String_.h"

namespace CSC1310
{
class Zip
{
   private:
	  Zip();
	  
   public:
      static Zip* getZip();
      virtual ~Zip();
	  
	  char* buffer_zip(const char* data_file_name, const char* zip_file_name, int& zip_file_length, char* unzipped_data_buffer, int unzipped_data_buffer_length);
	  CSC1310::String buffer_unzip(const char* data_file_name, const char* zip_file_name, char* zipped_data_buffer, int zipped_data_buffer_length);
	  
	  int zipit(const char* input_file_name, const char* output_file_name);
	  int unzipit(const char* input_file_name, const char* output_file_name);
};
}

#endif

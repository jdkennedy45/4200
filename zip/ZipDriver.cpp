#include "Zip.h"
#include "ReadFile.h"
#include "WriteFile.h"
#include <iostream>
#include <cstring>

int main()
{
	//Singleton
	CSC1310::Zip* zip = CSC1310::Zip::getZip();
	
	//const char* unzipped_data_buffer = {data obtained from network}
	//int unzipped_data_buffer_length = strlen(unzipped_data_buffer);
	
	const char* data_file_name_in = "endeavor_save_in.xml";
	const char* data_file_name_out = "endeavor_save_out.xml";
	
	const char* zip_file_name_in = "zip_endeavor_save_in.txt";
	const char* zip_file_name_out = "zip_endeavor_save_out.txt";
	
	//write the data obtained from the network to a file
	//CSC1310::WriteFile::entireFile(data_file_name_in, (char*) unzipped_data_buffer, unzipped_data_buffer_length);

	//zipit accepts a file name where the unzipped data is stored
    //and the desired zipped file name to store the zipped result
	zip->zipit(data_file_name_in, zip_file_name_in);

	int zipped_file_length = 0;
	char* zipped_file_c_str = CSC1310::ReadFile::entireFile(zip_file_name_in, &zipped_file_length);

	//transfer zipped_file_c_str over the network
	//you can use zipped_file_length as part of your protocol
	//to determine when you have received the entire file
	
	CSC1310::WriteFile::entireFile(zip_file_name_out, zipped_file_c_str, zipped_file_length);
	
	//unzipit accepts the file name of where the zipped data was stored
	//and the file name for the resulting unzipped data
	zip->unzipit(zip_file_name_out, data_file_name_out);
   
	int unzipped_file_length = 0;
	char* unzipped_file_c_str = CSC1310::ReadFile::entireFile(data_file_name_out, &unzipped_file_length);
	
	std::cout << unzipped_file_c_str << std::endl;
	return 0;
}


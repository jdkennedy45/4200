#include "SocketClient.h"
#include "WriteFile.h"
#include <iostream>
#include "Zip.h"
int main(int argv, char** argc)
{
	std::string ip_address = "127.0.0.1";
	int port_num = 6789;
	
	Poco::Net::initializeNetwork();
	SocketClient* socket_client = new SocketClient(ip_address, port_num);

	//have to keep main from ending until the client's task is complete
	while(!socket_client->isDone())
	{
		Sleep(100);
	}
	
	return 0;
}

void SocketClient::run()
{
	//what should this be set to?
	//if the file size is received first (as ascii characters) as part of the protocol
	//the buffer_size can be set to the exact required size
	int buffer_size = 50000;  
	char* buffer = new char[buffer_size];
	int num_bytes_received = 0;
	int buffer_index = 0;
    
    char zip_size_buffer[10];
    
    //Now retrieve the first message, which will contain the size of the zip file
    num_bytes_received = connection->receiveBytes(&zip_size_buffer[0], 20);
    std::cout << "num bytes received received from first message: " << num_bytes_received << endl;
    
    //retrieve the size of the zip file received in the first message
    int zip_file_size = atoi(zip_size_buffer);
    cout << "making new buffer with size: " << zip_file_size << endl;
    //make a new buffer to store the zip bytes in, with the size of the zip file gotten from first message
    char main_buffer[zip_file_size];
    
	//Now start receiving bytes from the zip
	num_bytes_received = connection->receiveBytes(&main_buffer[buffer_index], zip_file_size + 1);
    std::cout << endl << "num bytes received from zip file: " << num_bytes_received << endl;
	buffer_index = num_bytes_received - 1;
    
    //not using terminator, so check if the bytes received is lower than the total zip file size
    //if so, keep receiving bytes until we've got all the data
	while (num_bytes_received < zip_file_size)
    {  
		//this loop can be tricky as you may have received some, but not all, of the bytes
		//assume there will be enough room in the buffer for all of the bytes
		//TCP will give you all the bytes that it has received that have no errors and are in order
		//only ask for the number of bytes that you have room for in the buffer
		//start filling in the buffer where you left off last time
		num_bytes_received += connection->receiveBytes(&main_buffer[buffer_index+1], zip_file_size);
		std::cout << "total num bytes received from zip file: " <<  num_bytes_received << std::endl;
		//prepare to check the last byte received again for the null terminator
		buffer_index = num_bytes_received - 1;
   }
   

   //std::cout << num_bytes_received << std::endl;
   //std::cout << buffer_index << std::endl;
   //std::cout << buffer << std::endl;
   
   
   //get ready to write the buffer received to a zip file, then unzip that file
   //here we are strictly doing txt files...once moved to endeavor it will be .xml
   CSC1310::Zip* zip = CSC1310::Zip::getZip();
   cout << endl << "Getting the ZIP data received as ClientOutput.zip..." << endl;
   CSC1310::WriteFile::entireFile("ClientOutput.zip", main_buffer, num_bytes_received-1);
   cout << "Unzipping ZIP to ClientOutput.txt..." << endl;
   zip->unzipit("ClientOutput.zip", "ClientOutput.txt");
   
   //Sleep(10000);  //keep this client busy for 10 seconds
   
   delete[] buffer;
   done = true;
}

bool SocketClient::isDone()
{
	return done;
}

SocketClient::SocketClient(std::string ip_address, int port_num)
{
	done = false;

	Poco::Net::SocketAddress socket_addr(ip_address, port_num);
	connection = new Poco::Net::StreamSocket(socket_addr);

	client_thread = new Poco::Thread();
    client_thread->start(*this);
}

SocketClient::~SocketClient()
{
	std::cout << "destructor called" << std::endl;
	delete connection;
}

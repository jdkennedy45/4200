#include "SocketServer.h"
#include "ReadFile.h"
#include "WriteFile.h"
#include "Zip.h"

#include <iostream>
#include <string>
#include <cstring>

//BY JACOB KENNEDY
int main(int argc, char** argv)
{
    //pass filename on cmd as argument like so: "SocketServer ServerInput.txt"
	const char* file_name = argv[1];
    const char* zipped_input_file = "ServerInput.zip";
	int length = 0;
	Poco::Net::initializeNetwork();
    
	CSC1310::Zip* zip = CSC1310::Zip::getZip();
    zip->zipit(file_name, zipped_input_file);
    char* str = CSC1310::ReadFile::entireFile(zipped_input_file, &length);

	std::string ip_address = "127.0.0.1";
	int port_num = 6789;
    
	SocketServer* socket_server = new SocketServer(ip_address, port_num, str, length);

	socket_server->startServer();
	return 0;
}

//the send code is in its own server
//in case this takes a while, the server can wait for new connections
//in parallel (and then start their threads)
void SocketServer::run()
{
	SocketServer* socket_server = this; 
    
    //retrieve the zip file passed when object is created
    char* zip_file = socket_server->tcp_text;
    
    char zip_length_ascii[10];
    //retrieve the length of zip file from object
    int zip_length = socket_server->tcp_text_length;
    Poco::Net::StreamSocket connect();
    
    //convert zip_length to ascii in order to send as bytes (10 is just a padding, im expecting max 10 bytes)
    itoa(zip_length, zip_length_ascii, 10);
    //cout << "Length of zipped file size: " << zip_length_ascii << endl;
    
    //send file size seperately
    std::cout << endl << "sending zip file size to client" << std::endl;
    //sendbytes with the zip_lengh as ascii and the length of that
    int zip_size_seperate = client_connection.sendBytes(zip_length_ascii, strlen(zip_length_ascii));
    std::cout << "num bytes sent: " <<  zip_size_seperate << std::endl;

    //send rest now
	std::cout << "sending zip file to client" << std::endl;
    int zip_bytes = client_connection.sendBytes(zip_file, zip_length);
    std::cout << "num bytes sent: " <<  zip_bytes << std::endl;
    
    int num_bytes_sent = zip_size_seperate + zip_bytes;
    std::cout << endl << "total bytes sent to client: " << num_bytes_sent << endl;
}

SocketServer::SocketServer(std::string ip_address, int port_num, char* tcp_text, int tcp_text_length) 
{
	this->tcp_text = tcp_text;
	this->tcp_text_length = tcp_text_length;
	
	Poco::Net::SocketAddress socket_addr(ip_address, port_num);
	//creates a TCP welcoming socket
	server_socket = new Poco::Net::ServerSocket(socket_addr);
}

void SocketServer::startServer()
{
	while(true)
	{
		//blocks until connection made (can only handle one at a time)
		//could easily store an array of connections (5 for Endeavor)
		client_connection = server_socket->acceptConnection();

		server_thread = new Poco::Thread();
		server_thread->start(*this);  //the start method accepts a Runnable
	}
}

SocketServer::~SocketServer()
{
	std::cout << "destructor called" << std::endl;
	delete server_socket;
}

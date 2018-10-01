#if !defined SOCKET_SERVER
#define SOCKET_SERVER

//Poco includes must be first
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

#include "String_.h"

class SocketServer : public Poco::Runnable
{
   private:
		Poco::Net::StreamSocket client_connection; 
		Poco::Net::ServerSocket* server_socket;
		
		Poco::Thread* server_thread;
		
		char* tcp_text;
		int tcp_text_length;
		
   public:
		SocketServer(std::string ip_address, int port_num, char* text, int len);
		virtual ~SocketServer();
		void startServer();
		
		void run();
};

#endif

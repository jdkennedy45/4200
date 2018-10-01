#if !defined SOCKET_CLIENT
#define SOCKET_CLIENT

//Poco includes must be first
#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

#include "String_.h"

class SocketClient : public Poco::Runnable
{
   private:
		Poco::Net::StreamSocket* connection; 
		Poco::Thread* client_thread;
		bool done;

   public:
		SocketClient(std::string ip_address, int port_num);
		virtual ~SocketClient();
		void run();
		bool isDone();
		
		Poco::Net::StreamSocket* getConnection();
};

#endif

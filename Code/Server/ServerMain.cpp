#include "TronServer.h"
#include <memory>

int main()
{
	std::unique_ptr<Server> server (new Server());
	server->runServer();
	return 0;
}
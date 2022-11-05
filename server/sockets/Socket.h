#pragma once

#include <string.h>
#include <vector>

class Socket
{
public:
	Socket(int sock);

	/**
	 * Returns next char
	 */
	char *getNext();
	void sendResponse(char *res);
	~Socket();
	void dump(std::vector<char> &result);

private:
	int sock;
};

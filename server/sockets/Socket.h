#pragma once
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

private:
	int sock;
};

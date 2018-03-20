#ifndef SOCKETPOSECLIENT_H
#define SOCKETPOSECLIENT_H

#include "TinyTcpClient.h"
#include <functional>

class SocketPoseClient
{
public:
	SocketPoseClient();
	~SocketPoseClient();

	void sendPose(float pos[3], bool cv2gl = false);

private:
	void onConnect2(int session);
	void onDisconnect2(int session);
	void onRecv2(int session, const char *buf, int len);

	float mPos[3] = {0.0, 0.0, 0.0};
	TinyTcpClient mClient;

	OnConnect onConnect = nullptr;
	OnDisconnect onDisconnect = nullptr;
	OnRecv onRecv = nullptr;
};

#endif // SOCKETPOSECLIENT_H

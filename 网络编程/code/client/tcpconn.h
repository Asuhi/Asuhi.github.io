#pragma once
#include "head.h"

typedef std::map<std::string, std::list<std::string>> DirListType;

class TcpBase {
public:
	DirListType filelist; // map�����ļ�Ŀ¼�ṹ
public:
	ssize_t readn(int fd, void* buf, size_t count);
	ssize_t writen(int fd, void* buf, size_t count);
	ssize_t recv_peek(int sockfd, void *buf, size_t len);
	ssize_t readline(int sockfd, void *buf, size_t maxline);

};

class TcpFtp:public TcpBase {
public:
	int sock[2];//ָ����ļ������һ���׽���
public:

	bool ConnToSer(std::string addrs, int port);
	void GetDirInfo(int conn);
};


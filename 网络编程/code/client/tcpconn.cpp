#include "tcpconn.h"

bool TcpFtp::ConnToSer(std::string addrs, int port){
	struct sockaddr_in servaddr; //�ṹ�����
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET; //IPV4
	servaddr.sin_port = static_cast<in_port_t>(htons(port));//�˿ں� ʹ��htons()����ת���������ֽ���
	servaddr.sin_addr.s_addr = inet_addr(addrs.c_str());

	if ((sock[0] = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("�׽��ִ���ʧ��socket()");
		return false;
	}
	if (connect(sock[0], (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("����ʧ��connect()");
		return false;
	}

	if ((sock[1] = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("�׽��ִ���ʧ��socket()");
		return false;
	}
	if (connect(sock[1], (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		perror("����ʧ��connect()");
		return false;
	}

	return true;
}

ssize_t TcpBase::readn(int fd, void * buf, size_t count)
{
	size_t nleft = count;
	ssize_t nread;
	char * bufp = static_cast<char*>(buf);
	while (nleft > 0)
	{
		if ((nread = read(fd, bufp, nleft)) < 0)
		{
			if (errno == EINTR)//����źű��жϣ���ȻҪ�����������ݡ�
				continue;
			return -1;
		}
		else if (nread == 0)
			return count - nleft;
		bufp += nread;
		nleft -= nread;
	}
	return count;
}
ssize_t TcpBase::writen(int fd, void* buf, size_t count) {
	size_t nleft = count;	//ʣ����ֽ���nleft
	ssize_t nwritten;
	char *bufp = (char*)buf;
	while (nleft > 0) {
		if ((nwritten = write(fd, bufp, nleft)) < 0) {
			if (errno == EINTR)
				continue;
			return -1;
		}
		else if (nwritten == 0) {
			continue;
		}
		bufp += nwritten;
		nleft -= nwritten;
	}
	return count;
}
ssize_t TcpBase::recv_peek(int sockfd, void *buf, size_t len) {
	while (true) {
		ssize_t ret = recv(sockfd, buf, len, MSG_PEEK);

		if (ret == -1 && errno == EINTR)
			continue;
		return ret;
	}
}
ssize_t TcpBase::readline(int sockfd, void * buf, size_t maxline)
{
	int ret;
	int nread;
	char * bufp = static_cast<char*>(buf);
	int nleft = maxline;
	char tmp[1024] = { 0 };
	while (1)
	{
		ret = recv_peek(sockfd, buf, nleft);
		if (ret < 0)
			return ret;
		else if (ret == 0)//��ʾ�Է��ر����׽ӿ�
			return ret;
		nread = ret;//���յ����ֽ���
		int i;
		for (i = 0; i < nread; i++)
		{
			if (bufp[i] == '\n')
			{
				memset(bufp, 0, 1024);
				ret = readn(sockfd, bufp, i + 1);//ȡ�����ݲ��ӻ������Ƴ�
				if (ret != i + 1)//��������ʧ�ܣ�ֱ�ӷ���
				{
					exit(EXIT_FAILURE);
				}
				return ret;
			}
		}
		if (nread > nleft)//û������'\n'�������ó���
		{
			exit(EXIT_FAILURE);
		}
		nleft -= nread;
		ret = readn(sockfd, bufp, nread);
		if (ret != nread)//��������ʧ�ܣ�ֱ�ӷ���
		{
			exit(EXIT_FAILURE);
		}
		bufp += nread;//ָ��ƫ�ƣ��������'\n'ָ���Ѿ�ƫ��
	}
	return -1;
}
void TcpFtp::GetDirInfo(int conn) {
	char sendbuf[1024] = { 0 };
	char recvbuf[1024] = { 0 };
	std::string key;
	std::list<std::string> flist;

	sprintf(sendbuf,"socket0\nLS\n");
	writen(conn, sendbuf, strlen(sendbuf));
	memset(sendbuf, 0, sizeof(sendbuf));
	while (strncmp(recvbuf, "over", 4)) {
		readline(conn, recvbuf, 1024);

		if (!strncmp(recvbuf, "key#", 4)) {
			memset(recvbuf, 0, 1024);
 			readline(conn, recvbuf, 1024);

			key = std::string(recvbuf);
			readline(conn, recvbuf, 1024);

			while (strncmp(recvbuf, "end", 3)) {
				flist.push_back(std::string(recvbuf));
				memset(recvbuf, 0, 1024);
				readline(conn, recvbuf, 1024);

			}
			filelist.insert(std::pair<std::string, std::list<std::string>>(key, flist));
			key.clear();
			flist.clear();
		}
	}
	std::list<std::string> dirlist;
	dirlist = filelist.find(std::string("/usr/pub/\n"))->second;
	for (auto it = dirlist.begin(); it != dirlist.end(); it++) {
		std::cout << *it;
	}
}


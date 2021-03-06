// Họ và tên:Ngô Minh Phương
// Mã sinh viên: 16021629
// Chương trình Server thiế t lập và lắng nghe kết nối từ Client , nhận thông báo và chuyển ký tự in thường thành in hoa , trả lại cho CLient
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main()
{
	int listenfd, connfd, listenFort;
	pid_t childid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr, connClientAddr;
	listenFort = 9090;
	int listenQueue = 3;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		perror("Server bi loi !");
		return 1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9090);

	int bind_c = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (bind_c < 0)
	{
		perror("Bind loi!");
		return 1;
	}
	if (listen(listenfd, listenQueue) < 0)
	{
		perror("Listen loi!");
	}
	printf("Server dang nghe o cong %d\n", listenFort);

	while (1)
	{
		unsigned int addrLength = sizeof(cliaddr);
		int nbytes;
		char buffer[1000];
		int connClientSocket = accept(listenfd, (struct sockaddr *)&cliaddr, &addrLength);
		if (connClientSocket < 0)
		{
			perror("Accept error");
			return 1;
		}
		printf("Thong tin Client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		while (1)
		{
			nbytes = read(connClientSocket, buffer, sizeof(buffer));
			printf("%d\n", nbytes);
			if (nbytes == 0)
			{
				printf("Cho ket noi moi!");
				break;
			}
			if (nbytes < 0)
			{
				perror("Read error!");
				break;
			}
			for (int i = 0; i < sizeof(buffer); i++)
			{
				if (islower(buffer[i]))
				{
					buffer[i] = toupper(buffer[i]);
				}
			}
			nbytes = write(connClientSocket, buffer, sizeof(buffer));
			if (nbytes < 0)
			{
				perror("Write error!");
				break;
			}
		}
	}

	close(listenfd);
	printf("Dong ket noi!");

	return 0;
}
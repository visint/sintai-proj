// 发送端
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


using namespace std;

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0); 
	fflush(stdout); 
        int len = 0;
	int sock = -1;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
	{   
		cout<<"socket error"<<endl;	
		return false;
	}   

		struct sockaddr_in from;
	bzero(&from, sizeof(struct sockaddr_in));
	from.sin_family = AF_INET;
	from.sin_addr.s_addr = htonl(INADDR_ANY);
	from.sin_port = htons(10001);

	const int opt = 1;
	//设置该套接字为广播类型，
	int nb = 0;
	nb = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if(nb == -1)
	{
		cout<<"set socket error..."<<endl;
		return false;
	}

	struct sockaddr_in addrto;
	bzero(&addrto, sizeof(struct sockaddr_in));
	addrto.sin_family=AF_INET;
        
//	addrto.sin_addr.s_addr=inet_addr("192.168.3.255");
        addrto.sin_addr.s_addr=htonl(INADDR_BROADCAST);
	addrto.sin_port=htons(10001);
	int nlen=sizeof(addrto);

	{
		//从广播地址发送消息
		char smsg[] = {"abcdef"};
		int ret=sendto(sock, smsg, strlen(smsg), 0, (sockaddr*)&addrto, nlen);
		if(ret<0)
		{
			cout<<"send error...."<<ret<<endl;
		}
		else
		{		
			printf("send ok \n");	
		}

	}
char smsg1[100] = {0};
struct timeval timeout={4,0};
setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
int index = 0;
	len=sizeof(addrto);

        while(1)
        {
                //从广播地址发送消息
       		
                int ret=recvfrom(sock, smsg1, 100, 0, (struct sockaddr*)&from,(socklen_t*)&len);
		if(ret<=0)
		{
                       
	 		cout<<"recv timeout...."<<sock<<endl;
	                if(index++>2)
			{
 				close(sock);
				return 0;
			}		
		}
		else
		{		
			printf("recv package %s %s\n",inet_ntoa(from.sin_addr), smsg1);	
		}

		sleep(1); 
        }
	close(sock);
	return 0;
}


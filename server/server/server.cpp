
//
//
//#include <Winsock2.h>
//
//#include <stdio.h>
//#include <iostream>
//#pragma comment(lib,"ws2_32.lib")
//using namespace std;
//
//void main(void)
//
//{   
//
//      WSADATA wsaData;
//
//      SOCKET sockSrv;    
//	  SOCKET SOCKETsockConn;
//     
//
//      SOCKADDR_IN  addrSrv;
//
//      SOCKADDR_IN addrClient;//�������ܿͻ��˵ĵ�ַ��Ϣ
//
//      int len=sizeof(SOCKADDR);
//
//      WORD wVersionRequested;//����WinSock��İ汾��
//
//      int err;  
//
//     
//
//      wVersionRequested =MAKEWORD(2,2);//����һ������������汾�ŵ�WORDֵ
//
//     
//
//      err =WSAStartup(wVersionRequested, &wsaData);//�����׽��ֿ�
//
//      if ( err != 0 ) {//����ֵ������0�������˳���
//
//           return;
//
//      }
//
//     
//
//      if ( LOBYTE(wsaData.wVersion ) != 2 ||
//
//           HIBYTE(wsaData.wVersion ) != 2 ) {//�жϵ��ֽں͸��ֽ��Ƿ񶼵���1
//
//           WSACleanup( );//���ǵĻ������øú�������ֹ��Winsock���ʹ�ò�����
//
//           return;
//
//      }
//
// 
//
//      sockSrv=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//�����׽���
//
//     
//
//      addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
//
//      addrSrv.sin_family=AF_INET;
//
//      addrSrv.sin_port=htons(5150);
//
//      bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//���׽��ְ󶨵�����ַ��ָ���Ķ˿ں��ϡ�
//
//      listen(sockSrv,5);
//
// 
//
//     
//
//     SOCKETsockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
//
//      while(1)//��Ϊ�������ˣ���Ҫ���ϵصȴ��ͻ��˵���������ĵ������ڴ�������ѭ����
//
//      {
//
//           char recvBuf[100];
//
//           char sendBuf[100];//�ڵ�ǰ��������ӵ�һ���׽�����������������sockConn�����У���������׽��־Ϳ�����ͻ���ͨ�š���ǰ���׽����Լ��������ͻ��˵���������
//
//           //��������״̬���׽���
//
//           //���ͻ�������������ʱ���ú������ܸ����󣬽������ӣ�ͬʱ��������һ�����
//
//          
//
//           //sprintf(sendBuf,"Welcome%s you",inet_ntoa(addrClient.sin_addr));
//		   //cin>>sendBuf;
//		   scanf("%s\n",&sendBuf);
//
//           send(SOCKETsockConn,sendBuf,strlen(sendBuf)+1,0);//�÷��ص��׽��ֺͿͻ��˽���ͨ�š�
//
//          
//
//           recv(SOCKETsockConn,recvBuf,100,0);//�ӿͻ��˽�������
//
//           //printf("%s\n",recvBuf);
//		   printf("%s\n",recvBuf);
//           closesocket(SOCKETsockConn);//��ǰͨ�����֮����Ҫ����closesocket�����ر��ѽ������׽��֣��ͷ�Ϊ���׽��ַ������Դ��
//
//      }//Ȼ�������һ��ѭ�����ȴ���һ�ͻ�����ĵ�������������ѭ���Ļ����˴��������WSACleanup������ֹ���׽��ֿ��ʹ�á�
//
//}
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
using namespace std;
void main()
{
	int recv;
	WSADATA wsadata;
	int newsock;
	
	SOCKET socketfd;
	int len=sizeof(SOCKADDR_IN);
	SOCKADDR_IN server_addr;         //���������ڵĵ�ַ���˿ںţ�IP��Э�飩
	SOCKADDR_IN client_addr;         //�ͻ������ڵĵ�ַ
	WSAStartup(MAKEWORD(2,2),&wsadata);

	socketfd=socket(AF_INET,SOCK_STREAM,0);   //���������������ڼ�����socket

	//ΪSOCKADDR_INһϵ�в�����ֵ
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(5150);
	server_addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");

	//socket�ͷ������˵�ַ��
	bind(socketfd,(SOCKADDR*)&server_addr,sizeof(server_addr));
	cout<<"bind success!"<<endl;

	//�����ͻ��˵���������
	listen(socketfd,5);

	//�����µ�socket���ڴ���ȴ������еĿͻ�����������
	newsock=accept(socketfd,(SOCKADDR*)&client_addr,&len);
	cout<<"accept success!"<<endl;
	while(1)
		{
			char buf[20];
			recv=recvfrom(newsock,buf,20,0,(SOCKADDR*)&client_addr,&len);
			cout<<"recv success!"<<endl;
			printf("%s\n",buf);
	}
	closesocket(newsock);
    closesocket(socketfd);
	WSACleanup();

}
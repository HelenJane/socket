
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
//      SOCKADDR_IN addrClient;//用来接受客户端的地址信息
//
//      int len=sizeof(SOCKADDR);
//
//      WORD wVersionRequested;//保存WinSock库的版本号
//
//      int err;  
//
//     
//
//      wVersionRequested =MAKEWORD(2,2);//创建一个包含了请求版本号的WORD值
//
//     
//
//      err =WSAStartup(wVersionRequested, &wsaData);//加载套接字库
//
//      if ( err != 0 ) {//返回值不等于0，程序退出。
//
//           return;
//
//      }
//
//     
//
//      if ( LOBYTE(wsaData.wVersion ) != 2 ||
//
//           HIBYTE(wsaData.wVersion ) != 2 ) {//判断低字节和高字节是否都等于1
//
//           WSACleanup( );//不是的话，调用该函数，终止对Winsock库的使用并返回
//
//           return;
//
//      }
//
// 
//
//      sockSrv=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//创建套接字
//
//     
//
//      addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
//
//      addrSrv.sin_family=AF_INET;
//
//      addrSrv.sin_port=htons(5150);
//
//      bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//将套接字绑定到本地址和指定的端口号上。
//
//      listen(sockSrv,5);
//
// 
//
//     
//
//     SOCKETsockConn=accept(sockSrv,(SOCKADDR*)&addrClient,&len);
//
//      while(1)//作为服务器端，需要不断地等待客户端的连接请求的到来，在此设置死循环。
//
//      {
//
//           char recvBuf[100];
//
//           char sendBuf[100];//于当前这个新连接的一个套接字描述符，保存于sockConn变量中，利用这个套接字就可以与客户端通信。先前的套接字仍继续监听客户端的连接请求。
//
//           //返回连接状态的套接字
//
//           //当客户端连接请求到来时，该函数接受该请求，建立连接，同时它将返回一个相对
//
//          
//
//           //sprintf(sendBuf,"Welcome%s you",inet_ntoa(addrClient.sin_addr));
//		   //cin>>sendBuf;
//		   scanf("%s\n",&sendBuf);
//
//           send(SOCKETsockConn,sendBuf,strlen(sendBuf)+1,0);//用返回的套接字和客户端进行通信。
//
//          
//
//           recv(SOCKETsockConn,recvBuf,100,0);//从客户端接受数据
//
//           //printf("%s\n",recvBuf);
//		   printf("%s\n",recvBuf);
//           closesocket(SOCKETsockConn);//当前通信完成之后，需要调用closesocket函数关闭已建立的套接字，释放为该套接字分配的资源，
//
//      }//然后进入下一个循环，等待另一客户请求的到来。若不是死循环的话，此处还需调用WSACleanup函数终止对套接字库的使用。
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
	SOCKADDR_IN server_addr;         //服务器所在的地址（端口号，IP，协议）
	SOCKADDR_IN client_addr;         //客户端所在的地址
	WSAStartup(MAKEWORD(2,2),&wsadata);

	socketfd=socket(AF_INET,SOCK_STREAM,0);   //创建服务器端用于监听的socket

	//为SOCKADDR_IN一系列参数赋值
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(5150);
	server_addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");

	//socket和服务器端地址绑定
	bind(socketfd,(SOCKADDR*)&server_addr,sizeof(server_addr));
	cout<<"bind success!"<<endl;

	//监听客户端的请求连接
	listen(socketfd,5);

	//创建新的socket用于处理等待队列中的客户端连接请求
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
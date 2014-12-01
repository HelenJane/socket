# include <winsock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
 
using namespace std;
void main(void)

{

   WSADATA              wsaData;

   SOCKET               s;

   SOCKADDR_IN          ServerAddr;
  // SOCKADDR_IN          ClientAddr;

   int                  Port = 5150;
   

   //初始化Windows Socket 2.2

   WSAStartup(MAKEWORD(2,2), &wsaData);

   

   // 创建一个新的Socket来连接服务器

      s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   

   // 填写客户端地址信息

   // 端口为5150

   // 服务器IP地址为"136.149.3.29"，注意使用inet_addr将IP地址转换为网络格式

      ServerAddr.sin_family = AF_INET;

      ServerAddr.sin_port = htons(Port);    

      ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

 

   // 向服务器发出连接请求

      connect(s, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr)); 
	  cout<<"connect success!";
	  while(1)
	  {
		 // char *Sendbuf="hello, I am client!";
		  char Sendbuf[20];
		  //recv(s,Recvbuf,20,0);
		  //cout<<Recvbuf<<endl;
		 // printf("%s",Recvbuf);
		//  printf("recieve succsse!");
		  //cin>>Sendbuf;
		  //scanf("%s\n",&Sendbuf);
		  cin.getline(Sendbuf,20);       //从终端读取一行
		  sendto(s,Sendbuf,20,0,(SOCKADDR *)&ServerAddr,sizeof(ServerAddr));    //将bufer中的内容传送给服务器端
		  printf("send success!\n");
	  }
		  closesocket(s);
      

   // 新的连接建立后，就可以互相通信了，在这个简单的例子中，我们直接关闭连接，

   // 并关闭监听Socket，然后退出应用程序

      closesocket(s);

 

   // 释放Windows Socket DLL的相关资源

      WSACleanup();

}
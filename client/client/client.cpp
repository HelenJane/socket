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
   

   //��ʼ��Windows Socket 2.2

   WSAStartup(MAKEWORD(2,2), &wsaData);

   

   // ����һ���µ�Socket�����ӷ�����

      s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   

   // ��д�ͻ��˵�ַ��Ϣ

   // �˿�Ϊ5150

   // ������IP��ַΪ"136.149.3.29"��ע��ʹ��inet_addr��IP��ַת��Ϊ�����ʽ

      ServerAddr.sin_family = AF_INET;

      ServerAddr.sin_port = htons(Port);    

      ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

 

   // �������������������

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
		  cin.getline(Sendbuf,20);       //���ն˶�ȡһ��
		  sendto(s,Sendbuf,20,0,(SOCKADDR *)&ServerAddr,sizeof(ServerAddr));    //��bufer�е����ݴ��͸���������
		  printf("send success!\n");
	  }
		  closesocket(s);
      

   // �µ����ӽ����󣬾Ϳ��Ի���ͨ���ˣ�������򵥵������У�����ֱ�ӹر����ӣ�

   // ���رռ���Socket��Ȼ���˳�Ӧ�ó���

      closesocket(s);

 

   // �ͷ�Windows Socket DLL�������Դ

      WSACleanup();

}
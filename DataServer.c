#include <stdio.h>
#include <string.h>
#include <fstream>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024    /* 字串緩衝區長度 */
using namespace std;
int main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n;
  	char  	str[MAXLINE],str_r[MAXLINE],str_r2[MAXLINE],pass[50];
    char*    num;
    char*    rssi;
  	struct 	sockaddr_in   	serv, cli;
  	fstream  fout;
  	fout.open("RssiData.txt",ios::app|ios::out);
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用
    while(1)
    {
        serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

        //指定 socket 的 IP 位址和 port number
        serv.sin_family      = AF_INET;
        serv.sin_addr.s_addr = 0;
        serv.sin_port        = htons(5678);	// 指定port

        //UTC
        //bind(serv_sd, &serv, sizeof(serv)) ;
        bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

        listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態

        cli_len = sizeof(cli);
        printf("server waits for client\n");
        cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

        printf("connected!\n");
        int x = 0;
        while(x<10)
        {


            n=recv(cli_sd, str_r, MAXLINE, 0); //由server接收
            num = strtok(str_r,".");
            rssi = strtok(NULL,".");
            printf("第%s筆資料-> RSSI = %s \n",num,rssi);
            fout << "No." << num << " rssi = " << rssi << "\n";
            x+=1;
        }

        //結束 WinSock DLL 的使用
        closesocket(serv_sd);
        closesocket(cli_sd);
    }

   	WSACleanup();
   	system("pause");
}

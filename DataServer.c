#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n;
  	char  	str[MAXLINE],str_r[MAXLINE],str_r2[MAXLINE],pass[50];

  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�
    while(1)
    {
        serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

        //���w socket �� IP ��}�M port number
        serv.sin_family      = AF_INET;
        serv.sin_addr.s_addr = 0;
        serv.sin_port        = htons(5678);	// ���wport

        //UTC
        //bind(serv_sd, &serv, sizeof(serv)) ;
        bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

        listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A

        cli_len = sizeof(cli);
        printf("server waits for client\n");
        cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);

        printf("connected!\n");
        int x = 0;
        while(x<10)
        {


            n=recv(cli_sd, str_r, MAXLINE, 0); //��server����
            printf("server recv: %s (%d bytes)\n",str_r,n);
            x+=1;
        }

        //���� WinSock DLL ���ϥ�
        closesocket(serv_sd);
        closesocket(cli_sd);
    }

   	WSACleanup();
   	system("pause");
}

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>

#define USEPORT 1234

using namespace std;

int main()
{
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    //Windows中，AF_INET==PF_INET
    //Linux中，不同的版本这两者有微小差别.对于BSD是AF,对于POSIX是PF
    if (serverSock < 0){
    cout << "socket creation failed" << endl;
    exit(-1);
    }
    cout << "socket creation successfully" << endl;
    //****绑定ip和端口
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(USEPORT);
    //INADDR_ANY绑定所有IP
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //****绑定套接字
    if (bind(serverSock,(struct sockaddr*)&serverAddr,sizeof(struct sockaddr)) == -1)
    {
        cout << "Bind error, Port[" << USEPORT << "]" << endl;
        exit(-1);
    }
    
    //****监听
    if (listen(serverSock, 10) == -1)
    {
        cout << "Listen error!" << endl;
    }
    struct sockaddr clientAddr;
    
    int size = sizeof(struct sockaddr);
    int clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, (socklen_t*)&size);

    system("sudo python stop.py");
    //****通信
    while(1)
    {
        char revData[5];
        int ret = recv(clientSock,revData,5,0);
        if(ret > 0)
        {
            revData[ret] = 0x00;
            
            cout << "rev:" << revData << endl;
        }

        if(strcmp(revData, "UPUP") == 0)
        {
            system("sudo python up.py");
            printf("up\n");
        }
        else if(strcmp(revData, "DOWN") == 0)
        {
            system("sudo python down.py");
            printf("down\n");
        }
        else if(strcmp(revData, "LEFT") == 0)
        {
            system("sudo python left.py");
            printf("left\n");
        }
        else if(strcmp(revData, "RIGHT") == 0)
        {
            system("sudo python right.py");
            printf("right\n");
        }
        else if(strcmp(revData, "STOP") == 0)
        {
            system("sudo python stop.py");
            printf("stop\n");
        }
        else if(strcmp(revData, "QUIT") == 0)
        {
            cout<<"shutdown"<<endl;
            break;
        }
    }

    close(serverSock);
    return 0;
}


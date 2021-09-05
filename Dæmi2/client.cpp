#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
using namespace std;

int main(int argc, char *argv[])
{
    // Creating socket
    int socket1 = socket(AF_INET, SOCK_STREAM, 0);
    if (socket1 < 0)
    {
        cerr << "Error: " << hstrerror(errno) << endl;
        exit(1);
    }
 
    // Filling in server IP address and Port number
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
 
    char* hostIP;
    if (argc > 1)
        hostIP = argv[1];
 
    server.sin_family = AF_INET;
    short hostPort = 3000;
    if (argc >= 3)
        hostPort = (short)atoi(argv[2]);
    server.sin_port = htons(hostPort);
 
    // Connecting to the remote server
    int res = connect(socket1, (struct sockaddr*) &server, sizeof(server));
    if (res < 0)
    {
        cerr << "Error: " << hstrerror(errno) << endl;
        exit(1);
    }
 
    cout << "Connected" << endl;
    write(socket1, "SYS ls", 20);
    char buffer[1024];
    res = read(socket1, buffer, 1024);
    if (res < 0)
    {
        cerr << "Error: " << hstrerror(errno) << endl;
        exit(1);
    }
 
    cout << buffer;
 
    close(socket1);
    return 0;
}

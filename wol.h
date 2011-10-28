#ifndef WOL_H
#define WOL_H


#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include<QMessageBox>
#include<QString>
#include<QThread>
#include<string.h>
#define PORT 23

class wol
    {
    public:

        static int in_ether (char *bufp, unsigned char *addr);
        static int send_wol (QString string_mac);


    };

class attendre : public QThread
{

   private:
      void run()
      {
          //Là, tu met ton algo

      }
};


#endif // WOL_H

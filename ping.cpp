// ping2.c

#include <winsock2.h>  //Linker ws2_32.lib
#include <icmpapi.h>   //Linker iphlpapi.lib
#include <stdio.h>

int test()



  IP_OPTION_INFORMATION ioi;
  ICMP_ECHO_REPLY       ier;
  LPHOSTENT             Host;
  WSADATA               wsaData;
  IN_ADDR               iaAddr;
  HANDLE                hIcmp;
  int                   i;

  if(argc != 2) {
    printf("\nUsage: %s IP_ou_DNS\n", argv[0]);
    return 1;
  }

  if(WSAStartup(MAKEWORD(2, 2), &wsaData)) {
    printf("\nErreur: WSAStartup() !\n");
    WSACleanup();
    return 1;
  }

  iaAddr.s_addr = inet_addr(argv[1]);

  if(iaAddr.s_addr == INADDR_NONE)
    Host = gethostbyname(argv[1]);
  else
    Host = gethostbyaddr((char *)&iaAddr,
                         sizeof(IN_ADDR),
                         AF_INET);
  if(!Host) {
    printf("\nErreur: IP ou DNS non valide !\n");
    WSACleanup();
    return 1;
  }

  printf("\nPing vers...\n IP : %s\n DNS: %s\n",
         inet_ntoa((*(LPIN_ADDR)Host->h_addr_list[0])),
         Host->h_name);

  hIcmp = IcmpCreateFile();

  for(i = 0; i < 4; i++) {
    ioi.Ttl         = 255;
    ioi.Tos         = 0;
    ioi.Flags       = 0;
    ioi.OptionsSize = 0;
    ioi.OptionsData = NULL;

    IcmpSendEcho(hIcmp,
                 *(DWORD *)(*Host->h_addr_list),
                 NULL,
                 0,
                 &ioi,
                 &ier,
                 sizeof(ICMP_ECHO_REPLY),
                 5000);

    if(ier.Status) {
      printf("\nErreur: %ld !", ier.Status);
      break;
    }

    iaAddr.s_addr = ier.Address;

    printf("\nR\202ponse de %s  RTT=%ldms  TTL=%d",
           inet_ntoa(iaAddr),
           ier.RoundTripTime,
           ier.Options.Ttl);
  }

  printf("\n");
  IcmpCloseHandle(hIcmp);
  WSACleanup();
  return 0;
}


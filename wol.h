#ifndef WOL_H
#define WOL_H

#include <winsock2.h>
const int IP_HDRINCL=2; 	// Permet d'éviter d'intégrer #include <ws2tcpip.h> qui ne veux plus fonctionner

// ********************************************************
// Les librairies
// ********************************************************
//#pragma comment(lib,"ws2_32.lib")


// ********************************************************
// Les structures des différentes entetes
// ********************************************************
struct ipv4 // htons pour les ushort et htonl pour les ulong
        {
        unsigned char		ihl:4;		// L'ordre des champs ihl et Version est inversé
        unsigned char		version:4;		// L'ordre des champs ihl et Version est inversé
        unsigned char		tos;
        unsigned short		length;
        unsigned short		id;
        unsigned short		offset:5;		// Ajout d'offset2 afin de pouvoir utiliser l'invertion qui se fait de 8 bits en 8 bits et non pas en unsigned short
        unsigned short		flag_mf:1;		// L'ordre des champs offset et flag est inversé
        unsigned short		flag_df:1;		// L'ordre des champs offset et flag est inversé
        unsigned short		flag_zero:1;	// L'ordre des champs offset et flag est inversé
        unsigned short		offset2:8;		// L'ordre des champs offset et flag est inversé
        unsigned char		ttl;
        unsigned char		type;
        unsigned short		checksum;
        unsigned long		ip_source;
        unsigned long		ip_destination;
        };

struct udp // htons pour les ushort et htonl pour les ulong
        {
        unsigned short		port_source;
        unsigned short		port_destination;
        unsigned short		length;
        unsigned short		checksum;
        };

void initiation_des_variables(void);
void envoi_de_la_trame(void);/*
void sortie_avec_erreur(int);*/
//int convertion_char_int(int tampon);

#endif // WOL_H

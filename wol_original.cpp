    // ********************************************
// Nom du code		: WakeOnLan.cpp
// Auteur			: SebF@frameIP.com.pas.de.spam
// Date de création : 20 juillet 2003
// Version			: 1.5
// Licence			: Ce code est libre de toute utilisation.
//					  La seule condition existante est de faire référence au site www.frameip.com afin de respecter le travail d'autrui.
// ********************************************

// ********************************************************
// Reste à faire
// ********************************************************
//	2003.03.01 - Fermer proprement les socket

// ********************************************************
// RoadMap
// ********************************************************
//
//	Passage de la compilation en mode Release
//	Version graphique

// ********************************************************
// Suivi de projet
// ********************************************************
//
//	2003.07.30 - V1.5 - Suppression des 3 Warning
//
//	2003.07.23 - V1.4 - Ajout de mon email devant la séquence magique
//
//	2003.07.22 - V1.3 - Résolution du problème des 00, Je n'utilise plus strlen mais un compteur int que je gère moi même. Il y a avait une double erreur, l'utilisation de strlen dans memcpy et dans sendto.
//
//	2003.07.20 - V1.2 - Suppression du /NODEFAULTLIB:LIBCD.lib
//			  - Résolution du problème dans le nom de l'exe et du cpp
//			  - Envoi de la trame
//			  - Génération du code magique
//
//	2003.07.20 - V1.1 - Ajout de /NODEFAULTLIB:LIBCD.lib pour éviter les conflits de librairie
//			  - Suppression de la faute d'orthographe dans le nom du projet
//
//	2003.07.20 - V1.0 - Création du projet Cmd
//			  - Passage en Level 4
//			  - Suppretion du repertoire Debug
//			  - Control de la longueur
//			  - convertion des minuscule en majuscule
//			  - control que la saisie est bien une Mac adresse

// ********************************************************
// Les includes
// ********************************************************
#include <winsock2.h>
#include <cstdio>			// Pour les Sprintf
const int IP_HDRINCL=2; 	// Permet d'éviter d'intégrer #include <ws2tcpip.h> qui ne veux plus fonctionner

// ********************************************************
// Les librairies
// ********************************************************
#pragma comment(lib,"ws2_32.lib")

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

// ********************************************************
// Les procédures
// ********************************************************
void initiation_des_variables(void);
void gestion_des_arguments(int argc, char* argv[]);
void envoi_de_la_trame(void);
void sortie_avec_erreur(int);
int convertion_char_int(int tampon);
void affichage_du_resultat(void);

// ********************************************************
// Les variables
// ********************************************************
char mac[100];						// Adresse MAC
struct ipv4 entete_ipv4;			// Entete IP
struct udp entete_udp;				// Entete UDP
char data_a_envoyer[65535];			// Data
int longueur_de_data_a_envoyer;		// Longueur du char *, je n'utilise pas strlen car il y a des 0
char trame_a_envoyer[65535];		// Entete IP + Entete couche 4 + data

int main (int argc, char* argv[])
        {
        initiation_des_variables();
        gestion_des_arguments(argc,argv);
        envoi_de_la_trame();
        affichage_du_resultat();
        printf("\n");
        return(1);
        }

void initiation_des_variables(void)
        {
        // ********************************************************
        // Affichage de la banniere
        // ********************************************************
        printf("\nWakeOnLan -  Wake On Lan - Version 1.5");
        printf("\nCreate on July 20, 2003, Last compilation on Febury 01, 2004");
        printf("\nSebF@FrameIP.Com - http://www.FrameIP.Com");
        printf("\n");

        // ********************************************************
        // Initiation des arguments
        // ********************************************************
        strcpy(mac,"005004A364F3");

        // ********************************************************
        // Initialisation des data
        // ********************************************************
        strcpy(data_a_envoyer,"- My Email is : SebF@FrameIP.Com -");
        longueur_de_data_a_envoyer=(int)strlen(data_a_envoyer);

        // ********************************************************
        // Initialisation de l'entête UDP
        // ********************************************************
        entete_udp.port_source=htons(3333);
        entete_udp.port_destination=htons(53);
        entete_udp.length=htons(8);
        entete_udp.checksum=0;

        // ********************************************************
        // Initialisation de l'entete Ip
        // ********************************************************
        entete_ipv4.ihl=5;
        entete_ipv4.version=4;
        entete_ipv4.tos=0;
        entete_ipv4.length=htons((unsigned short)(20+strlen(trame_a_envoyer)));
        entete_ipv4.id=(unsigned short)htonl(67);
        entete_ipv4.offset=0;
        entete_ipv4.ttl=100;
        entete_ipv4.type=17;
        entete_ipv4.ip_source=inet_addr("10.10.10.10");
        entete_ipv4.ip_destination=INADDR_BROADCAST;
        }

void gestion_des_arguments(int argc,char* argv[])
        {
        int i;

        // ********************************************************
        // Affichage de l'aide
        // ********************************************************
        if ( (argc>1) && (strcmp(argv[1],"-?")==0) || (argc==1) )
                {
                printf("\n");
                printf("\n-?         Help");
                printf("\n-mac       Mac address       Default value : %s",mac);
                printf("\n\nsample :   wakeonlan.exe     -mac 00A0C54118F8");
                printf("\n\n");
                exit(0);
                }

        // ********************************************************
        // Récupération des arguments
        // ********************************************************
        for (i=1;i<argc;i=i+1)
                if (strcmp(strlwr(argv[i]),"-mac")==0)
                        strcpy(mac,argv[i+1]);

        // ********************************************************
        // Controle des arguments
        // ********************************************************
        if (strlen(mac)!=12)		// vérifie que la saisie est bien de 12 caractères
                sortie_avec_erreur(1);

        // Les codes 48 à 57 représentent les chiffres.
        // Les codes 65 à 90 représentent les majuscules.
        // Les codes 97 à 122 représentent les minuscules.

        for (i=0;i<(int)strlen(mac);i++) 	// Boucle parcourrant les caracteres saisis
                {
                if (int(mac[i])>=97&&int(mac[i])<=102) // Convertion des minuscules en majuscules
                        mac[i]=mac[i]-32;
                if ( (int(mac[i])>=48&&int(mac[i])<=57)==FALSE ) // Si ce n'est pas un nombre
                        if ( (int(mac[i])>=65&&int(mac[i])<=70)==FALSE ) // Si ce n'est pas l'une des 6 premières lettres
                                sortie_avec_erreur(2);
                }
        }

void envoi_de_la_trame(void)
        {
        WSADATA initialisation_win32;
        SOCKADDR_IN information_sur_la_destination;
        int nombre_de_caractere_emis;
        SOCKET id_de_la_socket;
        int tampon;
        int i,j;

        // ********************************************************
        // Initialisation de la Socket
        // **************************************************
        WSAStartup(MAKEWORD(2,2),&initialisation_win32);
        id_de_la_socket=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);

        // ********************************************************
        // Activation de l'envoi de l'entete IP
        // **************************************************
        tampon=1;
        setsockopt(id_de_la_socket,IPPROTO_IP,IP_HDRINCL,(char *)&tampon,sizeof(tampon));
        setsockopt(id_de_la_socket,SOL_SOCKET,SO_BROADCAST,(char *)&tampon,sizeof(tampon));
                // SO_BROADCAST permet l'utilisation de 255.255.255.255

        // ********************************************************
        // Création de la séquence magique (6 * FF + 16 * la Mac adresse)
        // ********************************************************
        tampon=255;
        for (i=0;i<6;i++)	// Ajout des 6 FF hexa pas les lettres FF !)
                {
                memcpy(data_a_envoyer+longueur_de_data_a_envoyer,&tampon,1);
                longueur_de_data_a_envoyer++;
                }

        for (j=0;j<16;j++)	// Ajout des 16 Mac address
                for (i=0;i<12;i=i+2) // Convertit la chaine contennant la Mac adresse en hexa
                        {
                        tampon=convertion_char_int(mac[i])*16+convertion_char_int(mac[i+1]);
                        memcpy(data_a_envoyer+longueur_de_data_a_envoyer,&tampon,1);
                        longueur_de_data_a_envoyer++;
                        }

        // ********************************************************
        // Préparation de la trame à envoyé
        // ********************************************************
        memcpy(trame_a_envoyer,(unsigned short *)&entete_ipv4,sizeof(struct ipv4));
        memcpy(trame_a_envoyer+sizeof(struct ipv4),(unsigned short *)&entete_udp,sizeof(struct udp));
        memcpy(trame_a_envoyer+sizeof(struct ipv4)+sizeof(struct udp),data_a_envoyer,longueur_de_data_a_envoyer);

        // ********************************************************
        // Paramètre nécessaire au sendto
        // ********************************************************
        information_sur_la_destination.sin_family=AF_INET;
        information_sur_la_destination.sin_addr.s_addr=entete_ipv4.ip_destination;

        // ********************************************************
        // Envoi de la trame
        // ********************************************************
        nombre_de_caractere_emis=sendto(id_de_la_socket,trame_a_envoyer,sizeof(struct ipv4)+sizeof(struct udp)+longueur_de_data_a_envoyer,0,(struct sockaddr*)&information_sur_la_destination,sizeof(information_sur_la_destination));
        if (nombre_de_caractere_emis<1)
                sortie_avec_erreur(3);

        // ********************************************************
        // Fermeture de la socket correspondant à la commande socket()
        // ********************************************************
        closesocket(id_de_la_socket);

        // ********************************************************
        // quite propement le winsock ouvert avec la commande WSAStartup
        // ********************************************************
        WSACleanup(); //  (A appeller autant de fois qu'il a été ouvert)
        }

void sortie_avec_erreur(int error)
        {
        if (error<3)
                printf("\nError, the Mac address format is not good\nError code : %d",error);
        if (error==3)
                printf("\nError, The magic sequence was not sent to %s address MAC\nError code : %d",mac,error);
        printf("\n\n");
        exit(0);
        }

int convertion_char_int(int caractere)
        {
        // ********************************************************
        // Convertion un caractere de type char en un nombre de type int
        // ********************************************************
        if ((caractere>=48&&caractere<=57)==TRUE)
                return(caractere-48);
        else
                return(caractere-55);
        }

void affichage_du_resultat()
        {
        // ********************************************************
        // Affichage du resultat
        // ********************************************************
        printf("\nThe magic sequence was sent to %s address MAC",mac);
        printf("\n\n");
        }

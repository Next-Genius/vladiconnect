#include "wol.h"


// ********************************************************
// Les variables
// ********************************************************
char mac[100];						// Adresse MAC
struct ipv4 entete_ipv4;			// Entete IP
struct udp entete_udp;				// Entete UDP
char data_a_envoyer[65535];			// Data
int longueur_de_data_a_envoyer;		// Longueur du char *, je n'utilise pas strlen car il y a des 0
char trame_a_envoyer[65535];		// Entete IP + Entete couche 4 + data



void initiation_des_variables(void)
       {


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
     /*   entete_ipv4.length=htons((unsigned short)(20+strlen(trame_a_envoyer)));
        entete_ipv4.id=(unsigned short)htonl(67);
        entete_ipv4.offset=0;
        entete_ipv4.ttl=100;
        entete_ipv4.type=17;
        entete_ipv4.ip_source=inet_addr("10.10.10.10");
        entete_ipv4.ip_destination=INADDR_BROADCAST;*/
        }
/*
void gestion_des_arguments(int argc,char* argv[])
        {
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
*/
void envoi_de_la_trame(void)
{
  /*  WSADATA initialisation_win32;
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
                        //tampon=convertion_char_int(mac[i])*16+convertion_char_int(mac[i+1]);
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
                //sortie_avec_erreur(3);

        // ********************************************************
        // Fermeture de la socket correspondant à la commande socket()
        // ********************************************************
        closesocket(id_de_la_socket);

        // ********************************************************
        // quite propement le winsock ouvert avec la commande WSAStartup
        // ********************************************************
        WSACleanup(); //  (A appeller autant de fois qu'il a été ouvert)*/
        }
/*
void sortie_avec_erreur(int error)
        {
        if (error<3)
                printf("\nError, the Mac address format is not good\nError code : %d",error);
        if (error==3)
                printf("\nError, The magic sequence was not sent to %s address MAC\nError code : %d",mac,error);
        printf("\n\n");
        exit(0);
        }*/
/*
int convertion_char_int(int caractere)
        {
        // ********************************************************
        // Convertion un caractere de type char en un nombre de type int
        // ********************************************************
        if ((caractere>=48&&caractere<=57)==TRUE)
                return(caractere-48);
        else
                return(caractere-55);
        }*/





#include "wol.h"

 int wol::in_ether (char *bufp, unsigned char *addr)
{
    char c, *orig;
    int i;
    unsigned char *ptr = addr;
    unsigned val;

    i = 0;
    orig = bufp;
    while ((*bufp != '\0') && (i < 6)) {
        val = 0;
        c = *bufp++;
        if (isdigit(c))
            val = c - '0';
        else if (c >= 'a' && c <= 'f')
            val = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            val = c - 'A' + 10;
        else {
#ifdef DEBUG
			QMessageBox::warning(0, "WOL", tr("Invalid ethernet address !"));
#endif
            //errno = EINVAL;
            return (-1);
        }
        val <<= 4;
        c = *bufp;
        if (isdigit(c))
            val |= c - '0';
        else if (c >= 'a' && c <= 'f')
            val |= c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            val |= c - 'A' + 10;
        else if (c == ':' || c == 0)
            val >>= 4;
        else {
#ifdef DEBUG
			QMessageBox::warning(0, "WOL", tr("Invalid ethernet address !"));
#endif
            //errno = EINVAL;
            return (-1);
        }
        if (c != 0)
            bufp++;
        *ptr++ = (unsigned char) (val & 0377);
        i++;

        // We might get a semicolon here - not required.
        if (*bufp == ':') {
            if (i == 6) {
                    ;           // nothing
            }
            bufp++;
        }
    }
        if (bufp - orig != 17) {
        return (-1);
    } else {
        return (0);
    }
}

int wol::send_wol (QString string_mac)
{
#if defined (WIN32)
    WSADATA WSAData;
    int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
#else
    int erreur = 0;
#endif

    if(erreur) {
		QMessageBox::warning(0, "WOL", tr("Error whith the initiation"));
        return(-1);
    }

    //Convertion de QString en char* sans const char*
    // créer le buffer pour copier la chaîne
    size_t size = string_mac.toStdString().size() + 1;
    char * mac = new char[ size ];
    // copier la chaîne
    strncpy( mac, string_mac.toStdString().c_str(), size );

    int packet;
    struct sockaddr_in sap;
    unsigned char ethaddr[8];
    unsigned char *ptr;
    unsigned char buf [128];
    int optval = 1;

    // Fetch the hardware address.
    if (in_ether (mac, ethaddr) < 0) {
		QMessageBox::warning(0, "WOL", tr("Invalid hardware address"));
        return (-1);
    }

    // setup the packet socket
    if ((packet = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		QMessageBox::warning(0, "WOL", tr("Socket failed"));
        return (-2);
    }

    // Set socket options
    if (setsockopt (packet, SOL_SOCKET, SO_BROADCAST, (char *)&optval,
                    sizeof (optval)) < 0) {
		QMessageBox::warning(0, "WOL", tr("Set socket failed"));
        closesocket (packet);
        return (-3);
    }

    // Set up broadcast address
    sap.sin_family = AF_INET;
    sap.sin_addr.s_addr = htonl(0xffffffff);        // broadcast address
    sap.sin_port = htons(60000);

    // Build the message to send - 6 x 0xff then 16 x MAC address
    ptr = buf;
    for (int i = 0; i < 6; i++)
        *ptr++ = 0xff;
    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 6; i++)
            *ptr++ = ethaddr [i];

    // Send the packet out
    if (sendto (packet, (char *)buf, 102, 0, (struct sockaddr *)&sap, sizeof (sap)) < 0) {
		QMessageBox::warning(0, "WOL", tr("Sendto failed"));
        closesocket (packet);
        return (-4);
    }
    closesocket (packet);
    // Si la plateforme est Windows
#if defined (WIN32)
    WSACleanup();
#endif
    return (0);
}


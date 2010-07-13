#include "cryptage.h"
/*
cryptage::cryptage()
{
}*/


QString cryptage::crypte(QString texte, QByteArray cle)
{

    QByteArray texteEnBytes = texte.toAscii();
    QByteArray codeFinal;
    int tailleCle = cle.length();

            for (int i = 0; i < texte.length(); ++i) {
                    codeFinal += char(texteEnBytes[i] ^ cle[i % tailleCle]);
            }

    return codeFinal.toHex();
}

QString cryptage::decrypte(QString texte, QByteArray cle)
{
    QByteArray texteEnBytes = QByteArray::fromHex(texte.toAscii());
    QByteArray codeFinal = "";

    for (int i = 0; i < texteEnBytes.length(); ++i) {
        codeFinal += char(texteEnBytes[i] ^ cle[i % cle.length()]);
    }

    return codeFinal;
}


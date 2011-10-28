#ifndef CRYPTAGE_H
#define CRYPTAGE_H

#include<time.h>    //srand
#include <QCryptographicHash>   //md5
#include <QByteArray>
#include<QBitArray>
#include<QtGlobal>  //qsrand
#include<QMessageBox>
class cryptage
{
public:
    //cyptage();
    static QString crypte(QString texte, QByteArray cle);
    static QString decrypte(QString texte, QByteArray cle);


};

#endif // CRYPTAGE_H

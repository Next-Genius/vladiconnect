/*******************************************************************
 This file is part of Vladiconnect
 Copyright (C) 2009-2010 Louis VICAINNE (louis.vicainne@gmail.com)

 Vladiconnect is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public Licence
 as published by the Free Software Foundation; either version 2
 of the Licence, or (at your option) any later version.

 Vladiconnect is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public Licence for more details.

 You should have received a copy of the GNU General Public Licence
 along with VladiConnect; if not, write to the Free Software Foundation,
 Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
********************************************************************/
#include "cryptage.h"

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


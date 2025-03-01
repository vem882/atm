#include "checker.h"


Checker::Checker()
{

}

void Checker::checkResourceFile(const QString &path)
{
    QFile file(path);
    if (!file.exists()) {
        //qDebug() << "Tiedostoa ei löydy polusta:" << path;
    } else {
        //qDebug() << "Tiedosto löytyi polusta:" << path;
    }
}



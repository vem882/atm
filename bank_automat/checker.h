#ifndef CHECKER_H
#define CHECKER_H

#include <QString>
#include <QDebug>
#include <QFile>


class Checker
{
public:
    Checker();
    void checkResourceFile(const QString &path);
};

#endif // CHECKER_H

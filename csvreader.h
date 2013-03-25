#ifndef CSVREADER_H
#define CSVREADER_H

#include "modelitem.h"

#include <QList>

class QObject;

class CSVReader
{
public:
    static QList<QObject*> Read(const QString& i_file);

};

#endif // CSVREADER_H

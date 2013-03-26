#ifndef CSVREADER_H
#define CSVREADER_H

#include "modelitem.h"
#include "modelcompany.h"

#include <QList>

class QObject;

class CSVReader
{
public:
    static void Read(ModelCompany& o_model_company, const QString& i_file);

};

#endif // CSVREADER_H

#include "csvreader.h"

#include <QObject>
#include <QFile>
#include <QStringList>

#include "modelitem.h"

QList<QObject*> CSVReader::Read(const QString& i_file)
{
    QList<QObject*> res;

    QFile file(i_file);
    if(file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            QString line = file.readLine();
            QStringList vals = line.split(',');
            ModelItem* model_item = new ModelItem(vals[0], vals[4].toDouble());
            res.append(model_item);
        }
        file.close();
    }

    return res;
}

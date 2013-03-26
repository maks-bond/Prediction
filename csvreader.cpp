#include "csvreader.h"

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QStringList>

#include "modelitem.h"

void CSVReader::Read(ModelCompany& o_model_company, const QString& i_file)
{
    QFile file(i_file);

    o_model_company.SetCompanyName(QFileInfo(file).baseName());

    if(file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            QString line = file.readLine();
            QStringList vals = line.split(',');
            ModelItem* model_item = new ModelItem(vals[0], vals[4].toDouble());
            o_model_company.AddItem(model_item);
        }
        file.close();
    }
}

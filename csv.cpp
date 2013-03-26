#include "csv.h"

#include <QDir>
#include <QDirIterator>

#include "modelcompany.h"
#include "modelitem.h"

QList<QString> CSV::Find(const QDir &i_dir)
{
    QStringList filters("*.csv");
    QDirIterator dir_iterator(i_dir.path(), filters, QDir::NoFilter, QDirIterator::Subdirectories);
    QList<QString> res;

    while(1)
    {
        if(dir_iterator.fileInfo().suffix() == "csv")
            res.append(dir_iterator.filePath());

        if(!dir_iterator.hasNext())
            break;

        dir_iterator.next();
    }

    return res;
}

void CSV::Read(ModelCompany& o_model_company, const QString& i_file)
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

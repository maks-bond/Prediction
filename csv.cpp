#include "csv.h"

#include <QDir>
#include <QDirIterator>

#include "datacompany.h"

namespace
{
    const QString g_date_format("yyyy-M-d");
}

QVector<QString> CSV::Find(const QDir &i_dir)
{
    QStringList filters("*.csv");
    QDirIterator dir_iterator(i_dir.path(), filters, QDir::NoFilter, QDirIterator::Subdirectories);
    QVector<QString> res;

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

DataCompany CSV::Read(const QString &i_file)
{
    QFile file(i_file);
    DataCompany data_company;
    data_company.SetCompanyName(QFileInfo(file).baseName());

    bool first_date_flag = true;

    //HERE WE ASSUME THAT DATES IS CONSEQUENTIAL!!!
    if(file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            QString line = file.readLine();
            QStringList vals = line.split(',');
            QDate cur_date = QDate::fromString(vals[0],g_date_format);

            if(first_date_flag)
            {
                if(cur_date.isValid())
                {
                    data_company.SetStartDate(cur_date);
                    first_date_flag = false;
                }
                else continue;
            }

            data_company.PushPrice(vals[4].toDouble());
        }
        file.close();
    }
    return data_company;
}

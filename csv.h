#ifndef CSV_H
#define CSV_H

#include <QVector>
#include <QString>

class QDir;
class DataCompany;

class CSV
{
public:
    // returns list of csv file names
    static QVector<QString> Find(const QDir& i_dir);
    static DataCompany* Read(const QString& i_file);

private:
    CSV(){}
};

#endif // CSV_H

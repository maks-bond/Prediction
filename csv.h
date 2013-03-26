#ifndef CSV_H
#define CSV_H

#include <QList>
#include <QString>

class QDir;
class ModelCompany;

class CSV
{
public:
    static QList<QString> Find(const QDir& i_dir);
    static void Read(ModelCompany& o_model_company, const QString& i_file);

private:
    CSV(){}
};

#endif // CSV_H

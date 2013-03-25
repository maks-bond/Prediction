#ifndef MODELITEM_H
#define MODELITEM_H

#include <QObject>
#include <QString>

class ModelItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString date READ date WRITE setDate)
    Q_PROPERTY(double price READ price WRITE setPrice)

public:
    explicit ModelItem(const QString& date, double price, QObject *parent = 0);
    double price(){return price_;}
    QString date(){return date_;}
    void setPrice(double p){price_=p;}
    void setDate(const QString& d) {date_=d;}
    
private :
    QString date_;
    double price_;
    
};

#endif // MODELITEM_H

#ifndef MODELITEM_H
#define MODELITEM_H

#include <QObject>
#include <QString>

class ModelItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString date READ date WRITE setDate)
    Q_PROPERTY(int price READ price WRITE setPrice)

public:
    explicit ModelItem(const QString& date, int price, QObject *parent = 0);
    int price(){return price_;}
    QString date(){return date_;}
    void setPrice(int p){price_=p;}
    void setDate(const QString& d) {date_=d;}
    
private :
    QString date_;
    int price_;
    
};

#endif // MODELITEM_H

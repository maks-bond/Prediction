#include "modelitem.h"

ModelItem::ModelItem(const QString& date, int price, QObject *parent) :
    date_(date),price_(price),QObject(parent)
{
}

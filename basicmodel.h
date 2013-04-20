#ifndef BASICMODEL_H
#define BASICMODEL_H

#include <QVector>
#include <QMetaType>

typedef QVector<int> Component;

typedef QVector<Component> BasicModel;

Q_DECLARE_METATYPE(BasicModel)

#endif // BASICMODEL_H

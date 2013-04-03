#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <model.h>
#include <modelitem.h>
#include <QDate>


class Recognizer
{
public:
    Recognizer(QDate& start, QDate& end);
    QList<ModelItem*> Forecast(const Model& model,int comp_index);

    void SetStartPeriod(QDate& start);
    void SetEndPeriod(QDate& end);

private :
    QDate m_period_start;
    QDate m_period_end;
};

#endif // RECOGNIZER_H

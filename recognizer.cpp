#include "recognizer.h"

Recognizer::Recognizer(QDate& start, QDate& end) : m_period_start(start), m_period_end(end)
{
}

QList<ModelItem *> Recognizer::Forecast(const Model &model, int comp_index)
{
    int f_size = m_period_start.daysTo(m_period_end);
    QList<ModelItem*> res;
    if(f_size <= 0)
        return res;
    QDate cur_date = m_period_start;
    for(int i=0;i<f_size;i++){
        // should be right format of date string
        ModelItem* cur = new ModelItem(cur_date.toString(),rand()%1000);
        res.append(cur);
    }
    return res;
}

void Recognizer::SetStartPeriod(QDate &start)
{
    if(start.isValid())
        m_period_start = start;
}

void Recognizer::SetEndPeriod(QDate &end)
{
    if(end.isValid())
        m_period_end = end;
}

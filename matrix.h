#ifndef MATHSTRUCTURES_H
#define MATHSTRUCTURES_H


#include <QVector>

class Matrix
{
public:
    typedef QVector<double> TVariable;
    typedef QVector<double> TTimeSlice;
    typedef QVector<int> TFilter;

    Matrix();
    Matrix(const QVector<TVariable >& i_matrix);

    void PushVariable(const TVariable& i_variable);
    void RemoveVariable(int index);
    bool IsEmpty() const;
    int GetVariablesNumber() const;
    int GetObservationNumber() const;
    const TVariable& GetVariable(int index) const;
    TTimeSlice GetTimeSlice(int i_time, const TFilter& i_filters = TFilter()) const;
    Matrix Filter(const TFilter& i_filters);

    double* Data() const;

private:
    QVector<TVariable > m_matrix;
};

#endif // MATHSTRUCTURES_H

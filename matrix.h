#ifndef MATHSTRUCTURES_H
#define MATHSTRUCTURES_H

#include <QMetaType>
#include <QVector>
#include <QSet>

class Matrix
{
public:
    typedef QVector<double> TVariable;
    typedef QVector<double> TTimeSlice;
    typedef QSet<int> TFilter;

    Matrix();
    Matrix(const QVector<TVariable >& i_matrix);

    void PushVariable(const TVariable& i_variable);
    void RemoveVariable(int index);
    bool IsEmpty() const;
    void Clear();
    int GetVariablesNumber() const;
    int GetObservationNumber() const;
    const TVariable& GetVariable(int index) const;
    TTimeSlice GetTimeSlice(int i_time, const TFilter& i_filters = TFilter()) const;
    //Matrix Filter(const TFilter& i_filters);

    //Memory leak is here!!!
    double* Data() const;

    bool operator ==(const Matrix& i_other) const;

private:
    QVector<TVariable > m_matrix;
};

Q_DECLARE_METATYPE(Matrix)

#endif // MATHSTRUCTURES_H

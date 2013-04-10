#ifndef MATHSTRUCTURES_H
#define MATHSTRUCTURES_H


#include <QVector>

class Matrix
{
public:
    typedef QVector<double> TVariable;

    Matrix();
    Matrix(const QVector<QVector<double> >& i_matrix);

    void PushVariable(const TVariable& i_variable);
    bool IsEmpty() const;
    int GetVariablesNumber() const;

private:
    QVector<QVector<double> > m_matrix;
};

#endif // MATHSTRUCTURES_H

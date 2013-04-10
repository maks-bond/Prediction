#include "mathstructures.h"

#include <stdexcept>

Matrix::Matrix()
{
}

Matrix::Matrix(const QVector<QVector<double> > &i_matrix)
    : m_matrix(i_matrix)
{
}

void Matrix::PushVariable(const Matrix::TVariable &i_variable)
{
    if((IsEmpty() && !i_variable.empty()) || (!IsEmpty() && m_matrix[0].size() == i_variable.size()))
    {
        m_matrix.push_back(i_variable);
        return;
    }

    throw std::logic_error("Bad variable!");
}

bool Matrix::IsEmpty() const
{
    return m_matrix.empty();
}

int Matrix::GetVariablesNumber() const
{
    if(!IsEmpty())
        return m_matrix[0].size();

    return 0;
}

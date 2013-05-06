#include "matrix.h"

#include <stdexcept>

Matrix::Matrix()
{
}

Matrix::Matrix(const QVector<TVariable > &i_matrix)
    : m_matrix(i_matrix)
{
}

void Matrix::PushFrontVariable(const Matrix::TVariable &i_variable)
{
    _PushVariable(i_variable, false);
}

void Matrix::PushVariable(const Matrix::TVariable &i_variable)
{
    _PushVariable(i_variable, true);
}

void Matrix::RemoveVariable(int index)
{
    if(index < 0 || index >= GetVariablesNumber())
        throw std::logic_error("Can't delete this variable");

    m_matrix.remove(index);
}

bool Matrix::IsEmpty() const
{
    return m_matrix.empty();
}

void Matrix::Clear()
{
    m_matrix.clear();
}

int Matrix::GetVariablesNumber() const
{
    if(!IsEmpty())
        return m_matrix.size();

    return 0;
}

int Matrix::GetObservationNumber() const
{
    if(!IsEmpty())
        return m_matrix[0].size();

    return 0;
}

const Matrix::TVariable& Matrix::GetVariable(int index) const
{
    if(index < 0 || index >= GetVariablesNumber())
        throw std::logic_error("Can't retrieve variable");
    return m_matrix[index];
}

Matrix::TTimeSlice Matrix::GetTimeSlice(int i_time, const TFilter& i_filters) const
{
    if(i_time < 0 || i_time >= GetObservationNumber())
        throw std::logic_error("Can't create time slice");

    TTimeSlice res;

    for(int i=0;i<GetVariablesNumber();i++)
    {
        if(i_filters.find(i) == i_filters.cend())
            res.push_back(m_matrix[i][i_time]);
    }

    return res;
}

/*Matrix Matrix::Filter(const TFilter& i_filters)
{
    Matrix res;
    int n = i_filters.size();

    for(int i=0;i<n;i++){
        int k = i_filters[i];
        res.PushVariable(m_matrix[k]);
    }

    return res;
}*/

double* Matrix::Data() const
{
    int m = GetObservationNumber(), n = GetVariablesNumber();
    double* res = new double[n*m];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            res[i*n+j] = m_matrix[j][i];
        }
    }
    return res;
}

bool Matrix::operator ==(const Matrix &i_other) const
{
    return m_matrix == i_other.m_matrix;
}

void Matrix::_PushVariable(const Matrix::TVariable &i_variable, bool i_is_back)
{
    if((IsEmpty() && !i_variable.empty()) || (!IsEmpty() && m_matrix[0].size() == i_variable.size()))
    {
        i_is_back ? m_matrix.push_back(i_variable) : m_matrix.push_front(i_variable);
        return;
    }

    throw std::logic_error("Bad variable!");
}


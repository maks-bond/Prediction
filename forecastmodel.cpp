#include "forecastmodel.h"
#include "alglib/interpolation.h"

#include <stdexcept>
#include <vector>

#include <QFile>
#include <QTextStream>

namespace
{
    void _WriteDoubleArray(const double* ip_array, int i_n, const QString& i_file_name)
    {
        QFile file(i_file_name);
        file.open(QFile::WriteOnly);

        QTextStream out(&file);

        for(int i = 0; i<i_n; ++i)
            out<<ip_array[i]<<" ";

        file.close();
    }

    void _WriteAlgLibArray(const alglib::real_1d_array& i_array, int i_n, const QString& i_file_name)
    {
        QFile file(i_file_name);
        file.open(QFile::WriteOnly);

        QTextStream text_stream(&file);

        for(int i = 0; i<i_n; ++i)
            text_stream<<i_array[i]<<" ";

        file.close();
    }

    void _WriteAlgLib2DArray(const alglib::real_2d_array& i_array, int i_rows, int i_columns, const QString& i_file_name)
    {
        QFile file(i_file_name);
        file.open(QFile::WriteOnly);

        QTextStream text_stream(&file);

        for(int i = 0; i<i_rows; ++i)
        {
            for(int j = 0; j<i_columns; ++j)
            {
                text_stream<<i_array(i, j)<<" ";
            }
            text_stream<<"\n";
        }

        file.close();
    }

    void _AddOnesVariable(Matrix& i_matrix)
    {
        Matrix::TVariable var(i_matrix.GetObservationNumber(), 1.0);
        i_matrix.PushFrontVariable(var);
    }
}

ForecastModel::ForecastModel()
    : m_is_computed(false),
      m_quality(-1)
{

}

ForecastModel::ForecastModel(const QVector<int> &i_a)
    : m_is_computed(false),
      m_quality(-1),
      m_a(i_a)
{

}

double ForecastModel::Evaluate(const QVector<double> i_a)
{
    if(!m_is_computed) throw std::logic_error("Set up model!");

    double res = 0;
    for(int j=0;j<i_a.size();j++) res+= i_a[j]*m_w[j];

    return res;
}

void ForecastModel::SetUp(const Matrix::TVariable &y, const Matrix &i_X)
{
    alglib::real_1d_array a_y;
    a_y.setcontent(y.size(),y.constData());
    alglib::real_2d_array a_X;
    Matrix X(i_X);
    _AddOnesVariable(X);
    a_X.setcontent(X.GetObservationNumber(), X.GetVariablesNumber(), X.Data());
    //_WriteDoubleArray(X.Data(), X.GetObservationNumber()*X.GetVariablesNumber(), "Double.out");
    //_WriteAlgLib2DArray(a_X, X.GetObservationNumber(), X.GetVariablesNumber(), "A2D.out");
    alglib::real_1d_array a_w;
    alglib::lsfitreport a_report;
    int a_code;
    alglib::lsfitlinear(a_y,a_X,a_code,a_w,a_report);
    //_WriteAlgLibArray(a_w, X.GetVariablesNumber() + 1, "1.out");

    if(a_code == -4) throw std::logic_error("Can't fit model!");

    double* p_w = a_w.getcontent();
    m_w = QVector<double>::fromStdVector(std::vector<double>(p_w,p_w+X.GetVariablesNumber()));
    m_is_computed = true;
    m_quality = a_report.avgerror;
}


double ForecastModel::Quality() const
{
    if(!m_is_computed) throw std::logic_error("Set up model!");
    return m_quality;
}

void ForecastModel::SetParams(QVector<int>& i_a)
{
    if(m_a == i_a) return;
    m_a = i_a;
    m_is_computed = false;
}

QVector<int> ForecastModel::GetParams() const
{
    return m_a;
}

ForecastModel ForecastModel::operator +(ForecastModel &i_other) const
{
    QVector<int> params(m_a);
    QVector<int> params_ad = i_other.GetParams();
    for(int i=0;i<params_ad.size();i++){
        params.push_back(params_ad[i]);
    }
    qSort(params);
    return ForecastModel(params);
}

bool ForecastModel::operator ==(const ForecastModel &i_other) const
{
    if(m_is_computed != i_other.m_is_computed)
        return false;

    if(m_is_computed)
        return m_w == i_other.m_w && m_a == i_other.m_a && m_quality == i_other.m_quality;

    return m_a == i_other.m_a;
}

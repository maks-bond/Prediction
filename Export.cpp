#include "Export.h"

#include <QFile>
#include <QTextStream>

namespace Export
{
    void Write(const Matrix::TVariable &i_variable, const QString &i_file_name)
    {
        QFile file(i_file_name);
        file.open(QIODevice::WriteOnly);

        QTextStream text_stream(&file);

        for(int i = 0; i<i_variable.size(); ++i)
            text_stream<<i_variable[i]<<'\n';
    }
}

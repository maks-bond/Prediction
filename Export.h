#ifndef EXPORTER_H
#define EXPORTER_H

#include "matrix.h"

#include <QString>

namespace Export
{
    void Write(const Matrix::TVariable& i_variable, const QString& i_file_name);
}
#endif // EXPORTER_H

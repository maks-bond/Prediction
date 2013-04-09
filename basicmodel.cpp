#include "basicmodel.h"

#include <stdexcept>

BasicModel::BasicModel()
{
}

void BasicModel::PushComponent(const Component &i_component)
{
    m_components.push_back(i_component);
}

const Component &BasicModel::GetComponent(int i) const
{
    if(i>=Size())
        throw std::logic_error("Bad index!");

    return m_components[i];
}

int BasicModel::Size() const
{
    return m_components.size();
}

bool BasicModel::operator ==(const BasicModel &i_other) const
{
    return m_components == i_other.m_components;
}

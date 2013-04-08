#ifndef BASICMODEL_H
#define BASICMODEL_H

#include <QVector>

struct Component
{};


class BasicModel
{
public:
    BasicModel();

    void PushComponent(const Component& i_component);
    const Component& GetComponent(int i) const;
    int Size() const;

private:
    typedef QVector<Component> TComponents;

    TComponents m_components;
};

#endif // BASICMODEL_H

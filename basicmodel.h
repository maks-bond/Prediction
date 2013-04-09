#ifndef BASICMODEL_H
#define BASICMODEL_H

#include <QVector>
#include <QMetaType>

struct Component
{
    Component() {}
    Component(const QVector<int>& i_data) : m_data(i_data){}

    bool operator ==(const Component& i_other) const
    {
        return m_data == i_other.m_data;
    }

    QVector<int> m_data;
};


class BasicModel
{
public:
    BasicModel();

    void PushComponent(const Component& i_component);
    const Component& GetComponent(int i) const;
    int Size() const;

    bool operator ==(const BasicModel& i_other) const;

private:
    typedef QVector<Component> TComponents;

    TComponents m_components;
};

Q_DECLARE_METATYPE(BasicModel)

#endif // BASICMODEL_H

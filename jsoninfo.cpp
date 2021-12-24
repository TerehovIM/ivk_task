#include "jsoninfo.h"

JsonInfo::JsonInfo()
{    

}
JsonInfo::JsonInfo(int id, QString name, bool status, float price)
{
    this->id = id;
    this->name = name;
    this->status = status;
    this->price = price;
}
int JsonInfo::getId() const
{
    return id;
}
QString JsonInfo::getName() const
{
    return name;
}
bool JsonInfo::getStatus() const
{
    return status;
}
float JsonInfo::getPrice() const
{
    return price;
}
void JsonInfo::setId(int value)
{
    id = value;
}
void JsonInfo::setName(const QString &value)
{
    name = value;
}
void JsonInfo::setStatus(bool value)
{
    status = value;
}
void JsonInfo::setPrice(float value)
{
    price = value;
}

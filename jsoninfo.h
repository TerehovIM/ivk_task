#ifndef JSONINFO_H
#define JSONINFO_H

#include <QString>

class JsonInfo
{
public:
    JsonInfo();
    JsonInfo(int id, QString name, bool status, float price);
    int getId() const;
    QString getName() const;
    bool getStatus() const;
    float getPrice() const;
    void setId(int value);
    void setName(const QString &value);
    void setStatus(bool value);
    void setPrice(float value);
private:
    int id;
    QString name;
    bool status;
    float price;
};

#endif // JSONINFO_H

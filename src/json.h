#ifndef JSON_H
#define JSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QFile>
#include <QJsonArray>

class json
{
public:
    json();
    bool saveJson(QString);
    QStringList readJson();
    bool removeText(QString);
};

#endif // JSON_H

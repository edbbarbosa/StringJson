#include "json.h"

json::json() {}

bool json::saveJson(QString str){
    const QString path = "data.json";
    QJsonArray texts;

    QFile file(path);
    if(file.exists()){
        if(!file.open(QIODevice::ReadOnly)){
            qWarning() << "Error:" << file.errorString();
            return false;
        }

        QJsonParseError error;
        const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        file.close();

        if(error.error != QJsonParseError::NoError || !doc.isArray()){
            qWarning() << "The file doesn't contain a valid JSON array";
            return false;
        }

        texts = doc.array();
    }

    texts.append(str);

    if(!file.open(QIODevice::WriteOnly)){
        qWarning() << "Error:" << file.errorString();
        return false;
    }

    file.write(QJsonDocument(texts).toJson(QJsonDocument::Indented));
    return true;
}

QStringList json::readJson(){
    QFile file("data.json");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "The file could not be opened:"
                   << file.errorString();
        return {};
    }

    QJsonParseError error;
    const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);

    if(error.error != QJsonParseError::NoError || !document.isArray()){
        qWarning() << "Invalid JSON or the content is not an array:"
                   << error.errorString();
        return {};
    }

    QStringList texts;
    const QJsonArray array = document.array();

    for(const QJsonValue &value : array){
        if(value.isString())
            texts.append(value.toString());
    }

    return texts;
}

bool json::removeText(QString str){
    const QString path = "data.json";
    QFile file(path);

    if(!file.exists()){
        qWarning() << "The file doesn't exit";
        return false;
    }

    if(!file.open(QIODevice::ReadOnly)){
        qWarning() << "Error:" << file.errorString();
        return false;
    }

    QJsonParseError error;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    file.close();

    if(error.error != QJsonParseError::NoError || !doc.isArray()){
        qWarning() << "The file doesn't contain a valid JSON array";
        return false;
    }

    QJsonArray texts = doc.array();
    bool found = false;

    for(int i = 0; i < texts.size(); ++i){
        if(texts[i].isString() && texts[i].toString() == str){
            texts.removeAt(i);
            found = true;
            break;
        }
    }

    if(!found){
        qWarning() << "The text was not found in the JSON";
        return false;
    }

    if(!file.open(QIODevice::WriteOnly)){
        qWarning() << "Error:" << file.errorString();
        return false;
    }

    file.write(QJsonDocument(texts).toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

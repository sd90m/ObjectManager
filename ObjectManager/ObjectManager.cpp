#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>

#include <iostream>

#include "Object.h"
#include "ObjectManager.h"

using namespace std;

ObjectManager::ObjectManager(QObject *parent)
    :QObject(parent)
{

}

void ObjectManager::onObjectRemove(const QUuid &objId)
{
    this->removeObject(objId);
}

QJsonArray ObjectManager::getObjects()
{
    auto path = QString("Path storage objects");

    if (QFile::exists(path) == false) {
        cout << "Objects file not exist, path:" << path.toStdString() << endl;
        return QJsonArray();
    }

    QFile file(path);
    if (file.open(QIODevice::OpenModeFlag::ReadOnly) == false) {
        cout << "Error on open objects file, path:" << path.toStdString() << "message:" << file.errorString().toStdString() << endl;
        return QJsonArray();
    }

    QJsonParseError jError;
    auto jDoc = QJsonDocument::fromJson(
                file.readAll(), &jError
                );

    if (jError.error != QJsonParseError::NoError) {
        cout << "Error on parce objects file, path:" << path.toStdString() <<  "message:" << jError.errorString().toStdString() << endl;
        return QJsonArray();
    }

    return jDoc.array();
}

void ObjectManager::getObjectFromRadar()
{
    QJsonObject jObj; //jObj = ...data from Radar on real time (5 Hz); query data from UI, for example
    Object obj(jObj);

    this->saveObject(obj);

    emit this->sendObject(obj);
}

void ObjectManager::getObjectFromStorage(const QUuid &id, const QDateTime &dateTime)
{
    auto jArray = this->getObjects();

    for (auto value: jArray) {

        Object obj(value.toObject());

        if(obj.id() == id && obj.dateTime() == dateTime) {
            emit this->sendObject(obj);
        }
    }
}

void ObjectManager::saveObject(const Object &obj)
{
    //save JSON on objects file
    emit this->objectSave(obj.id());
}

void ObjectManager::removeObject(const QUuid &objId)
{
    //remove JSON from objects file
    emit this->objectRemove(objId);
}

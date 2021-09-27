#include <QJsonObject>

#include "Object.h"

QHash<QString, Object::State> Object::SateName = {
      {QString("found"), Object::State::Found}
    , {QString("leading"), Object::State::Leading}
    , {QString("lost"), Object::State::Lost}
    , {QString("unknown"), Object::State::Unknown}
};


Object::Object(const QJsonObject &obj)
{
    this->init(obj);
}

const QJsonObject &Object::json() const
{
    return this->_obj;
}

const QUuid &Object::id() const
{
    return this->_id;
}

const QDateTime &Object::dateTime() const
{
    return this->_dateTime;
}

const Object::State &Object::state() const
{
    return this->_state;
}

void Object::init(const QJsonObject &obj)
{
    this->_obj      = obj;
    this->_id       = QUuid(obj["id"].toString());
    this->_state    = Object::SateName[obj["state"].toString()];
    this->_dateTime = QDateTime::fromString(obj["ps"].toString(), QString("dd.MM.yyy hh:mm:ss.zzz"));
}

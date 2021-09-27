#ifndef OBJECT_H
#define OBJECT_H

#include <QUuid>
#include <QHash>
#include <QDateTime>

class QJsonObject;
class QDateTime;

class Object
{
public:
    explicit Object(const QJsonObject& obj);
    ~Object() = default;

    enum class State {
        Found,
        Leading,
        Lost,
        Unknown
    };

    static QHash<QString, Object::State> SateName;

    const QJsonObject& json() const;
    const QUuid& id() const;
    const QDateTime& dateTime() const;
    const State& state() const;

private:
    QUuid _id;
    QDateTime _dateTime;
    State _state;
    QJsonObject _obj;

    void init(const QJsonObject& obj);
};

#endif // OBJECT_H

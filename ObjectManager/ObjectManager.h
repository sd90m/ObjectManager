#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QMap>
#include <QDateTime>
#include <QObject>

class Object;

class ObjectManager: public QObject
{
    Q_OBJECT

public:
    explicit ObjectManager(QObject* parent = nullptr);
    ~ObjectManager() = default;

signals:
    void objectSave(const QUuid&);
    void objectRemove(const QUuid&);
    void objectChange(const QUuid&);

    void sendObject(const Object&);

public slots:
    void onObjectRemove(const QUuid& objId);

private:
    QJsonArray getObjects();

    void getObjectFromRadar();
    void getObjectFromStorage(const QUuid& id, const QDateTime& dateTime);

    void saveObject(const Object& obj);
    void removeObject(const QUuid& objId);

};

#endif // OBJECTMANAGER_H

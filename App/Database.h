#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QTextStream>
#include <QDebug>

#include "human.h"
#include "org.h"

class Database
{
public:
    Database(const QString& filePath);
    void addUser(const Human& user, const ORG& org);
    QVector<QPair<Human*, ORG*>> readAllData();
    int getCount() const noexcept { return idCounter; }

private:
    void loadJsonFile();
    void saveJsonFile();

    QString filePath;
    QJsonArray jsonArray;
    int idCounter;
};

#endif // DATABASE_H

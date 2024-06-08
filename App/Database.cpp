#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QTextStream>
#include <QDebug>

#include "Database.h"

Database::Database(const QString& filePath) : filePath(filePath), idCounter(0)
{
    loadJsonFile();
}

void Database::addUser(const Human& user, const ORG& org)
{
    QJsonObject userObject;
    userObject["FIO"] = user.GetFIO();
    userObject["Name"] = user.GetName();
    userObject["Surname"] = user.GetSurname();
    userObject["FatherName"] = user.GetFatherName();
    userObject["Birthday"] = user.GetBirthday();
    userObject["Address"] = user.GetAddress();
    userObject["Actions"] = user.GetActions();
    userObject["Titul"] = user.GetTitul();
    userObject["Number"] = user.GetNumber();
    userObject["Email"] = user.GetEmail();
    userObject["Facebook"] = user.GetFacebook();
    userObject["Occupation"] = user.GetOccupation();
    userObject["INN"] = user.GetINN();
    userObject["Comment"] = user.GetComment();

    QJsonObject orgObject;
    orgObject["Name"] = org.GetName();
    orgObject["Right"] = org.GetRight();
    orgObject["INN"] = org.GetINN();
    orgObject["Birthday"] = org.GetBirthday();
    orgObject["Death"] = org.GetDeath();
    orgObject["OKVED"] = org.GetOKVED();
    orgObject["Actions"] = org.GetActions();
    orgObject["Address"] = org.GetAddress();
    orgObject["Site"] = org.GetSite();
    orgObject["Number"] = org.GetNumber();
    orgObject["Email"] = org.GetEmail();
    orgObject["Comment"] = org.GetComment();

    QJsonObject recordObject;
    recordObject["User"] = userObject;
    recordObject["Organization"] = orgObject;

    QString id = QString("ID%1").arg(++idCounter);  // Increment idCounter and create ID string
    QJsonObject idObject;
    idObject[id] = recordObject;

    jsonArray.append(idObject);

    saveJsonFile();
}

QVector<QPair<Human*, ORG*>> Database::readAllData()
{
    QVector<QPair<Human*, ORG*>> data;
    loadJsonFile();

    for (const QJsonValue& value : jsonArray)
    {
        QJsonObject idObject = value.toObject();
        for (const QString& key : idObject.keys())
        {
            QJsonObject recordObject = idObject[key].toObject();
            QJsonObject userObject = recordObject["User"].toObject();
            QJsonObject orgObject = recordObject["Organization"].toObject();

            Human* user = new Human(userObject);
            ORG* org = new ORG(orgObject);
            data.append(qMakePair(user, org));
        }
    }

    return data;
}

void Database::loadJsonFile()
{
    qDebug() << "loadJsonFile()";

    QFile file(filePath);
    if (!file.exists())
    {
        qWarning() << "File does not exist:" << filePath;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file for reading:" << filePath;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError)
    {
        qWarning() << "Error parsing JSON file:" << parseError.errorString();
        return;
    }

    if (document.isArray())
    {
        jsonArray = document.array();
        idCounter = jsonArray.size();
    }

    qDebug() << jsonArray;
}

void Database::saveJsonFile()
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file for writing:" << filePath;
        return;
    }

    QJsonDocument document(jsonArray);
    QTextStream stream(&file);
    stream << document.toJson();
    file.close();
}

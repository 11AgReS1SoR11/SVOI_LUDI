#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QTextStream>
#include <QDebug>

class User {
public:
    QString GetFIO() const { return "Full Name"; }
    QString GetName() const { return "Name"; }
    QString GetSurname() const { return "Surname"; }
    QString GetFatherName() const { return "Father Name"; }
    QString GetBirthday() const { return "Birthday"; }
    QString GetAddress() const { return "Address"; }
    QString GetActions() const { return "Actions"; }
    QString GetTitul() const { return "Title"; }
    QString GetNumber() const { return "Number"; }
    QString GetEmail() const { return "Email"; }
    QString GetFacebook() const { return "Facebook"; }
    QString GetOccupation() const { return "Occupation"; }
    QString GetINN() const { return "INN"; }
    QString GetComment() const { return "Comment"; }
};

class Organization {
public:
    QString GetName() const { return "OrgName"; }
    QString GetRight() const { return "OrgRight"; }
    QString GetINN() const { return "OrgINN"; }
    QString GetBirthday() const { return "OrgBirthday"; }
    QString GetDeath() const { return "OrgDeath"; }
    QString GetOKVED() const { return "OrgOKVED"; }
    QString GetActions() const { return "OrgActions"; }
    QString GetAddress() const { return "OrgAddress"; }
    QString GetSite() const { return "OrgSite"; }
    QString GetNumber() const { return "OrgNumber"; }
    QString GetEmail() const { return "OrgEmail"; }
    QString GetComment() const { return "OrgComment"; }
};

class Database {
public:
    Database(const QString& filePath) : filePath(filePath), idCounter(0) {
        loadJsonFile();
        idCounter = jsonArray.size();  // Initialize idCounter based on existing data
    }

    void addUser(const User& user, const Organization& org) {
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

    QVector<QPair<User, Organization>> readAllData() {
        QVector<QPair<User, Organization>> data;
        loadJsonFile();

        for (const QJsonValue& value : jsonArray) {
            QJsonObject idObject = value.toObject();
            for (const QString& key : idObject.keys()) {
                QJsonObject recordObject = idObject[key].toObject();
                QJsonObject userObject = recordObject["User"].toObject();
                QJsonObject orgObject = recordObject["Organization"].toObject();

                User user(userObject);
                Organization org(orgObject);
                data.append(qMakePair(user, org));
            }
        }

        return data;
    }

        // fio = json["FIO"].toString();
        // name = json["Name"].toString();
        // surname = json["Surname"].toString();
        // fatherName = json["FatherName"].toString();
        // birthday = json["Birthday"].toString();
        // address = json["Address"].toString();
        // actions = json["Actions"].toString();
        // titul = json["Titul"].toString();
        // number = json["Number"].toString();
        // email = json["Email"].toString();
        // facebook = json["Facebook"].toString();
        // occupation = json["Occupation"].toString();
        // inn = json["INN"].toString();
        // comment = json["Comment"].toString();

private:
    QString filePath;
    QJsonArray jsonArray;
    int idCounter;

    void loadJsonFile() {
        QFile file(filePath);
        if (!file.exists()) {
            qWarning() << "File does not exist:" << filePath;
            return;
        }

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Could not open file for reading:" << filePath;
            return;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument document = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qWarning() << "Error parsing JSON file:" << parseError.errorString();
            return;
        }

        if (document.isArray()) {
            jsonArray = document.array();
        }
    }

    void saveJsonFile() {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Could not open file for writing:" << filePath;
            return;
        }

        QJsonDocument document(jsonArray);
        QTextStream stream(&file);
        stream << document.toJson();
        file.close();
    }
};
#include "Database.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    User user;
    Organization org;
    Database db("../Data.json");

    db.addUser(user, org);
    db.addUser(user, org);
    db.addUser(user, org);

    return a.exec();
}
#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFileInfo>
#include <QDir>

#include <QSqlQuery>

#include <human.h>
#include <org.h>
#include <neuro.h>
#include <cardform.h>

namespace Ui {
class CardWindow;
}

class CardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardWindow(const QString &filename, QWidget *parent = nullptr);
    ~CardWindow();

    bool Connection_to_database(QSqlDatabase& db);

    int AddPerson();
    int AddORG();
    int AddPhone(const QString& PhoneNumber, const QString& PhoneTiedId);
    int AddTied(const QString& UserId, const QString& OrgId, const QString& Position, const QString& Email, const QString& image_path);

public slots:
    void on_pushButton_clicked();

protected:
    Ui::CardWindow *ui;
    CardForm* Card;
    QSqlDatabase db;
    QString imagepath;
};

#endif // CARDWINDOW_H

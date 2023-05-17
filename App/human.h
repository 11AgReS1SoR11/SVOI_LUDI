#ifndef HUMAN_H
#define HUMAN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class Human;
}

class Human : public QWidget
{
    Q_OBJECT

public:
    explicit Human(QWidget *parent = nullptr);
    ~Human();
    QString GetFIO();
    QString GetName();
    QString GetSurname();
    QString GetFatherName();
    QString GetBirthday();
    QString GetAddress();
    QString GetActions();
    QString GetTitul();
    QString GetNumber();
    QString GetEmail();
    QString GetFacebook();
    QString GetOccupation();
    QString GetINN();
    QString GetComment();
    void SetTextFIO(const QString& text);
    void SetTextAddress(const QString& text);
    void SetTextNumber(const QString& text);
    void SetTextEmail(const QString& text);
    void SetTextOccupation(const QString& text);
    void SetTextBirthday(const QString& text);
    void SetTextINN(const QString& text);
    void SetTextAction(const QString& text);


private:
    Ui::Human *ui;
    QFormLayout *Layout;
    QLineEdit* FIO;
    QLineEdit* Birthday;
    QLineEdit* Address;
    QLineEdit* Actions;
    QLineEdit* Titul;
    QLineEdit* Number;
    QLineEdit* Email;
    QLineEdit* Facebook;
    QLineEdit* Occupation;
    QLineEdit* INN;
    QLineEdit* Comment;
};

#endif // HUMAN_H

#ifndef ORG_H
#define ORG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QLineEdit>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui
{
class ORG;
}

class ORG : public QWidget
{
    Q_OBJECT
public:
    explicit ORG(QWidget *parent = nullptr);
    explicit ORG(const QJsonObject& json, QWidget* parent = nullptr);
    ~ORG();
    QString GetName() const;
    QString GetRight() const;
    QString GetINN() const;
    QString GetBirthday() const;
    QString GetDeath() const;
    QString GetOKVED() const;
    QString GetActions() const;
    QString GetAddress() const;
    QString GetSite() const;
    QString GetNumber() const;
    QString GetEmail() const;
    QString GetComment() const;
    void SetTextName(const QString& text);
    void SetTextAddress(const QString& text);
    void SetTextPravo(const QString& text);
    void SetTextINN(const QString& text);
    void SetTextBirthday(const QString& text);
    void SetTextDeath(const QString& text);
    void SetTextOKVED(const QString& text);
    void SetTextAction(const QString& text);
    void SetTextSite(const QString& text);
    void SetTextEmail(const QString& text);

private:
    Ui::ORG *ui;
    QFormLayout *Layout;
    QLineEdit* Name;
    QLineEdit* Right;
    QLineEdit* INN;
    QLineEdit* Birthday;
    QLineEdit* Death;
    QLineEdit* OKVED;
    QLineEdit* Actions;
    QLineEdit* Address;
    QLineEdit* Site;
    QLineEdit* Number;
    QLineEdit* Email;
    QLineEdit* Comment;
};

#endif // ORG_H

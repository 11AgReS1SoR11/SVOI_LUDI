#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QDialog>
#include <QVBoxLayout>

#include "cardform.h"

namespace Ui
{
class CardView;
}

class CardView : public QDialog
{
    Q_OBJECT

public:
    explicit CardView(const QStringList& Design, QWidget *parent = nullptr);
    ~CardView();

private:
    void SetPersonInformation(QPair<Human*, ORG*>& my_query);
    void SetORGInformation(QPair<Human*, ORG*>& my_query);
    void SetPictures(const QString& filename);

public slots:
    void cardReview(QPair<Human*, ORG*>, int);
    void on_pushButton_clicked();

private:
    Ui::CardView *ui;
    CardForm* Card;
};

#endif // CARDVIEW_H

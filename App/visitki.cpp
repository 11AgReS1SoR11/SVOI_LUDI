#include "visitki.h"
#include "ui_visitki.h"
#include <QSqlError>
#include <QSqlDatabase>

visitki::visitki(const QStringList& Design, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::visitki)
{
    ui->setupUi(this);

    setWindowTitle("СВОИ ЛЮДИ - Мои визитки");

    const int height = 200;
    const int width = 300;

    my_vis = new CardView(Design, this);
    QFormLayout *gLayoutChoiceRegion = new QFormLayout();
    query = new QSqlQueryModel;

    query->setQuery("select * from `opd`.`человек` inner join `opd`.`связь` ON `человек`.id_человек = `связь`.`объект1` where `визитка` is not null;");
    int x = query->rowCount();
    QPushButton* buttons[x];
    connect(this, &visitki::visitka,my_vis, &CardView::show_sl);
    for(int i = 0; i < x; i++)
    {
            // добавление кнопок
            QString FIO = query->data(query->index(i,1)).toString() + " " + query->data(query->index(i,2)).toString() + " " + query->data(query->index(i,3)).toString();
            buttons[i] = new QPushButton(FIO);
            buttons[i]->setStyleSheet(Design[0]);
            buttons[i]->setMinimumHeight(height);
            // слот для конопок
            connect(buttons[i], SIGNAL(clicked()), SLOT(Slot()));
            // добавление картинок
            QString filename = query->data(query->index(i, 23)).toString();
            QPixmap pixmap(filename);
            QLabel* Field = new QLabel(parent);
            Field->setFixedSize(width, height);
            pixmap.scaled(Field->size(), Qt::KeepAspectRatio);
            Field->setScaledContents(true);
            Field->setPixmap(pixmap);

            // добавляем в layout
            gLayoutChoiceRegion->addRow(Field, buttons[i]);
    }


    // Располагаться будут на виджете
    QWidget *widgetChoiceRegion = new QWidget();
    widgetChoiceRegion->setLayout(gLayoutChoiceRegion);

    // Помещаем виджет с кнопками в скролл зону
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widgetChoiceRegion);



    // Для размещения скролл-зоны с кнопками на group box
    // нужно будет создать еще один компоновщик - компоновщик group box
    // поместим на нем скролл-зону
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(scrollArea);

    QGroupBox *groupBoxChoiceRegion = new QGroupBox();
    groupBoxChoiceRegion->setLayout(vBoxLayout);


    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout();
    vBoxLayoutMain->addWidget(groupBoxChoiceRegion);



    QPushButton* Back = new QPushButton(this);
    Back->setText("Назад");
    Back->setMinimumHeight(50);
    Back->setStyleSheet(Design[0]);
    vBoxLayoutMain->addWidget(Back);

    widgetChoiceRegion->setStyleSheet(Design[3]);

    setLayout(vBoxLayoutMain);

    connect(Back, &QPushButton::clicked, this, &visitki::onBackButtonClicked);
}

visitki::~visitki()
{
    delete ui;
}

void visitki::show_visitk()
{
    this->show();
}

void visitki::onBackButtonClicked()
{
    this->close();
}

void visitki::Slot()
{
    QPushButton *button = (QPushButton *)sender();
    QStringList FIO = button->text().split(" ");
    QSqlQuery query;
    query.exec(QString("select * from `opd`.`человек`"
                "inner join `opd`.`связь` ON `человек`.`id_человек` = `связь`.`объект1`"
                "inner join `opd`.`организация` ON `организация`.`id_организация` = `связь`.`объект2`"
                       "where `фамилия` = '%1' and `имя` = '%2' and `визитка` is not null;").arg(FIO[0]).arg(FIO[1]));
    query.next();
    for (int i = 0; i < 24; i++)
    {
        qDebug() << query.value(i).toString();
    }
    qDebug() << query.lastError().text();
    emit visitka(query);
}




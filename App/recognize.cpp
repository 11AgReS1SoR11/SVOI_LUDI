#include "recognize.h"
#include "ui_recognize.h"

Recognize::Recognize(const QStringList& Design, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recognize)
{
    ui->setupUi(this);

    setWindowTitle("СВОИ ЛЮДИ - Загрузить визитку");

    // Пока картинка не выбрана - чёрный цвет
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::black);
    ui->Image->setAutoFillBackground(true);
    ui->Image->setPalette(palette);

    ui->ChooseFileButton->setMinimumHeight(35);
    ui->OK->setMinimumHeight(35);
    ui->ChooseFileButton->setStyleSheet(Design[0]);
    ui->OK->setStyleSheet(Design[0]);
}

Recognize::~Recognize()
{
    delete ui;
}

void Recognize::on_ChooseFileButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(this, "Выбрать картинку", "C:/Users/79916/Pictures", "jpg image (*.jpg);; png image (*.png);");

    QPixmap Picture_Pixmap(str);
    Picture_Pixmap = Picture_Pixmap.scaled(ui->Image->size(), Qt::KeepAspectRatio);
    ui->Image->setPixmap(Picture_Pixmap);
    if (str.size() != 0)
        ui->ChooseFileButton->setText(str);
}


void Recognize::on_OK_clicked()
{
    if (ui->Image->pixmap().isNull())
    {
        QMessageBox::warning(nullptr, tr("Внимание"),
                             tr("Выберите изображение"),
                             QMessageBox::Ok);
    }
    else
    {
        cardwin = new CardWindow(ui->ChooseFileButton->text(), this);
        cardwin->exec();
        this->close();
    }
}





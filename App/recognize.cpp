#include "recognize.h"
#include "ui_recognize.h"
#include <QStandardPaths>

Recognize::Recognize(const QStringList& Design, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recognize)
{
    ui->setupUi(this);

    setWindowTitle("СВОИ ЛЮДИ - Загрузить визитку");

    // Until the picture is selected, the color is black
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::black);
    ui->Image->setAutoFillBackground(true);
    ui->Image->setPalette(palette);

    // Set button design
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
    // Open the file explorer and get filepath
    QString str = QFileDialog::getOpenFileName(
        this, "Выбрать картинку", 
        ".."/*TODO: QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)*/, 
        "jpg image (*.jpg);;png image (*.png);;All files (*.*)"
    );
    ui->ChooseFileButton->setText(str);

    // Get image
    QPixmap Picture_Pixmap(str);
    Picture_Pixmap = Picture_Pixmap.scaled(ui->Image->size(), Qt::KeepAspectRatio);
    ui->Image->setPixmap(Picture_Pixmap);
}


void Recognize::on_OK_clicked()
{
    // If the picture is not selected, the reminder window pops up
    if (ui->Image->pixmap()->isNull())
    {
        QMessageBox::warning(nullptr, tr("Внимание"),
                             tr("Выберите изображение"),
                             QMessageBox::Ok);
    }
    else // The recognition process
    {
        cardwin = new CardWindow(ui->ChooseFileButton->text(), this);
        cardwin->exec();
        this->close();
    }
}

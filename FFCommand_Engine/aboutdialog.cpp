#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QDesktopServices>
aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);

}

aboutDialog::~aboutDialog()
{
    delete ui;
}

void aboutDialog::on_label_2_linkActivated(const QString &link)
{

    QDesktopServices::openUrl(QUrl("http://www.colorlab.com/"));
}

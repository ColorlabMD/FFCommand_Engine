#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class aboutDialog;
}

class aboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit aboutDialog(QWidget *parent = nullptr);
    ~aboutDialog();

private slots:
    void on_label_2_linkActivated(const QString &link);

private:
    Ui::aboutDialog *ui;
};

#endif // ABOUTDIALOG_H

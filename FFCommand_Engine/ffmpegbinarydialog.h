//-----------------------------------------------------------------------------
// This file is part of FFCommand Engine
//
// Copyright (c) 2019 Thomas Aschenbach, Colorlab Corporation
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2 of the License, or (at your
// option) any later version.
//
//   FFCommand Engine is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------

#ifndef FFMPEGBINARYDIALOG_H
#define FFMPEGBINARYDIALOG_H

#include <QDialog>

namespace Ui {
class ffmpegbinaryDialog;
}

class ffmpegbinaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ffmpegbinaryDialog(QWidget *parent = nullptr);
    ~ffmpegbinaryDialog();
    QString location;
    void setup(QString currentloc);
private slots:
    void on_setfolder_btn_clicked();

    void on_location_le_textChanged(const QString &arg1);


private:
    Ui::ffmpegbinaryDialog *ui;

};

#endif // FFMPEGBINARYDIALOG_H

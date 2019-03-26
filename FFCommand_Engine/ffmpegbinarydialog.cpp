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


#include "ffmpegbinarydialog.h"
#include "ui_ffmpegbinarydialog.h"
#include <QFileDialog>
ffmpegbinaryDialog::ffmpegbinaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ffmpegbinaryDialog)
{

    ui->setupUi(this);

}

ffmpegbinaryDialog::~ffmpegbinaryDialog()
{

    delete ui;

}
void ffmpegbinaryDialog::setup(QString currentloc)
{
    ui->location_le->setText(currentloc);
    location= currentloc;
}

void ffmpegbinaryDialog::on_setfolder_btn_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    location,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
        location=dir;

    ui->location_le->setText(location);
}

void ffmpegbinaryDialog::on_location_le_textChanged(const QString &arg1)
{
    location=ui->location_le->text();
}

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


#ifndef OUTPUTFILEFORM_H
#define OUTPUTFILEFORM_H

#include <QWidget>
#include "ffmpegarg.h"
namespace Ui {
class OutputFileForm;
}

class OutputFileForm : public QWidget
{
    Q_OBJECT

public:
    explicit OutputFileForm(QWidget *parent = nullptr);
    ~OutputFileForm();
    Ui::OutputFileForm *ui;
    QString OutputFilename;
    QString OutputDir;
    QStringList outputstringlist();
    void addrow(QString p,QString v);
    void setoutputfilename(QString ofn);
    bool batchmode;
    void setforbatch(bool);
signals:

    void updateneeded();

private slots:
    void on_add_param_btn_clicked();



    void on_delete_param_btn_clicked();


    void on_outputfile_le_textChanged(const QString &arg1);

    void on_outputparam_table_cellChanged(int row, int column);



    void on_outputfile_btn_clicked();

    void on_set_dir_btn_clicked();

private:

    QList < ffcommand>  ffcommandglobal_list;
};

#endif // OUTPUTFILEFORM_H

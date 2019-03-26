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

#ifndef PRESETSAVEDIALOG_H
#define PRESETSAVEDIALOG_H

#include <QDialog>

namespace Ui {
class PresetSaveDialog;
}

class PresetSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PresetSaveDialog(QWidget *parent = nullptr);
    ~PresetSaveDialog();
   void  setup(QStringList);
QString file;
QString comment;
private slots:
   void on_buttonBox_accepted();

private:
    Ui::PresetSaveDialog *ui;
    QStringList PresetsCats;

};

#endif // PRESETSAVEDIALOG_H

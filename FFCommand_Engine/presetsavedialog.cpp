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


#include "presetsavedialog.h"
#include "ui_presetsavedialog.h"

PresetSaveDialog::PresetSaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetSaveDialog)
{
    ui->setupUi(this);
}

PresetSaveDialog::~PresetSaveDialog()
{
    delete ui;

}
void  PresetSaveDialog::setup(QStringList inlist)
{
    for(int d=0; d<inlist.count(); d++)
    {
        ui->comboBox->addItem(inlist[d].mid(0,inlist[d].length()-4));
    }


}

void PresetSaveDialog::on_buttonBox_accepted()
{
    file = ui->comboBox->currentText()+".txt";
    comment="#"+ui->lineEdit->text();
}

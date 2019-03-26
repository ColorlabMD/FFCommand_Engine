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



#include "outputfileform.h"
#include "ui_outputfileform.h"
#include <QFileDialog>
OutputFileForm::OutputFileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputFileForm)
{
    ui->setupUi(this);

    ui->set_dir_btn->setVisible(false);
batchmode=false;
ui->outputparam_table->setSelectionBehavior(ui->outputparam_table->SelectRows);
ui->outputparam_table->setSelectionMode(ui->outputparam_table->SingleSelection);
ui->outputparam_table->setDragDropMode(ui->outputparam_table->InternalMove);
 ui->outputparam_table->setDropIndicatorShown(true);
ui->outputparam_table->setDragDropOverwriteMode(false);
}

OutputFileForm::~OutputFileForm()
{
    delete ui;



}

void OutputFileForm::on_add_param_btn_clicked()
{
    int rowadd = ui->outputparam_table->rowCount();
    ui->outputparam_table->insertRow(rowadd);

    QTableWidgetItem *newItem1 = new QTableWidgetItem(QString());
    QTableWidgetItem *newItem2 = new QTableWidgetItem(QString());

    ui->outputparam_table->setItem(rowadd,0,newItem1);
    ui->outputparam_table->setItem(rowadd,1,newItem2);
}

void OutputFileForm::addrow(QString p,QString v)
{
    int rowadd = ui->outputparam_table->rowCount();
    ui->outputparam_table->insertRow(rowadd);

    QTableWidgetItem *newItem1 = new QTableWidgetItem(QString(p));
    QTableWidgetItem *newItem2 = new QTableWidgetItem(QString(v));

    ui->outputparam_table->setItem(rowadd,0,newItem1);
    ui->outputparam_table->setItem(rowadd,1,newItem2);
}
void OutputFileForm::on_delete_param_btn_clicked()
{
    ui->outputparam_table->removeRow(  ui->outputparam_table->currentRow());

}
QStringList OutputFileForm::outputstringlist()
{
    QStringList out;
    QString p, r;
    for(int i=0; i<ui->outputparam_table->rowCount();i++)
    {
        if (ui->outputparam_table->item(i,0))
            p= ui->outputparam_table->item(i,0)->text();
        if (ui->outputparam_table->item(i,1))
            r= ui->outputparam_table->item(i,1)->text().toUtf8();
        out.append(p);
        out.append(r);
    }
    return out;
}

void OutputFileForm::on_outputfile_le_textChanged(const QString &arg1)
{
    // OutputFilename =OutputDir+"/"+arg1;
    OutputFilename=arg1;
    emit updateneeded();
}
void  OutputFileForm::setoutputfilename(QString ofn)
{


    ui->outputfile_le->setText(ofn);

}

void OutputFileForm::on_outputparam_table_cellChanged(int row, int column)
{
    emit updateneeded();
}


void OutputFileForm::setforbatch(bool bm)
{

    if (bm)
    {
        ui->set_dir_btn->setVisible(true);
        batchmode=true;
        ui->outputfile_btn->setVisible(false);
        ui->label->setText("Append Input File Name");

    }
    else {

        ui->set_dir_btn->setVisible(false);
        batchmode=false;
        ui->outputfile_btn->setVisible(true);

        ui->label->setText(" Output File Name");
    }

    emit updateneeded();
}
void OutputFileForm::on_outputfile_btn_clicked()
{

    QString filename = QFileDialog::getSaveFileName(
                this,tr("Output File"),".","*.*");
    if(filename.isEmpty()) return;
    ui->outputfile_le->setText(filename);
    emit updateneeded();
}

void OutputFileForm::on_set_dir_btn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
        OutputDir=dir;
    emit updateneeded();
}

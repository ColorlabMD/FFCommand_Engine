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


#include "processqueuedialog.h"
#include "ui_processqueuedialog.h"
#include <QTextBrowser>
processqueueDialog::processqueueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::processqueueDialog)
{
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowTitleHint |Qt::WindowMinimizeButtonHint);
    this->setWindowTitle("Process Queue");
    running=false;
}

processqueueDialog::~processqueueDialog()
{
    delete ui;
}


void processqueueDialog::enqueue( QList<ffprocessobj *> processq)

{
    ui->processqueue_table->clear();
    while ( ui->processqueue_table->rowCount()>0)
    {
        ui->processqueue_table->removeRow(0);
    }
    //processq.clear();

    for(int i =0; i<processq.count(); i++)
    {
        //int rowadd = ui->processqueue_table->rowCount();
        ui->processqueue_table->insertRow(i);
        QTextBrowser * w= new QTextBrowser();
        w->append(processq.at(i)->args);
        QTableWidgetItem *newItem1 = new QTableWidgetItem(QString(processq.at(i)->Status ));
        //  QTableWidgetItem *newItem2 = new QTableWidgetItem(QString(processq.at(i)->args));
        ui->processqueue_table->setCellWidget(i,1,w);
        ui->processqueue_table->setItem(i,0,newItem1);
        //ui->processqueue_table->setItem(i,1,newItem2);
    }

}
void processqueueDialog::stopqueue()
{
    ui->startstop_btn->setText("start queue");
    running=false;

}

void processqueueDialog::on_startstop_btn_clicked()
{
    if (running == false)
    {
        running=true;
        ui->startstop_btn->setText("stop queue");
        emit  queuestatechange();
    }
    else
    {

        running=false;
        ui->startstop_btn->setText("start queue");
        emit  queuestatechange();

    }

}

void processqueueDialog::on_clear_btn_clicked()
{
    emit  requestclear();

}

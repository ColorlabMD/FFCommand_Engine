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

#include "ffprocessobj.h"
#include "ui_ffprocessobj.h"
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
ffprocessobj::ffprocessobj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ffprocessobj)
{

    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowTitleHint |Qt::WindowMinimizeButtonHint);
    Status = "queued";
    process = new QProcess();
    timer=new QElapsedTimer();
    ffmpeglocation= "/usr/local/bin";
    length  =0.00001;
}


ffprocessobj::~ffprocessobj()
{
    delete ui;
}
void ffprocessobj::process_stdout()
{

    QByteArray ba;
    ba = process->readAllStandardOutput();
    ba += process->readAllStandardError();
    QString checkd;


    checkd = QString::fromUtf8(ba.data());


    ui->textBrowser->append((QString::fromUtf8(ba.data())));

    if (checkd.contains("Overwrite ? [y/N]"))
    {



        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "File Exists", "Overwrite?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            process->write("y\n" );

        } else {
            process->write("N\n" );
        }
    }


    if (checkd.contains("Duration:"))
    {

        int c= checkd.lastIndexOf("Duration:");
        QString ld = checkd.mid(c+10,11);
        //qDebug()<<"Duration"<<ld;
        QStringList qsl = ld.split(":");
        // qDebug()<<ld.count()<<"Duration"<<ld;
        if (qsl.count()==3)
        {

            length = qsl[0].toInt() *60 *60;

            length += qsl[1].toInt()  *60;
            length +=qsl[2].toDouble() ;

            //qDebug()<<"Duration"<<qsl[0]<<qsl[1]<<qsl[2]<<"l= "<<length;

        }

    }


    if (checkd.contains("time="))
    {

        double ctime;
        int c= checkd.lastIndexOf("time=");
        QString ld = checkd.mid(c+5,11);
        //qDebug()<<"Time"<<ld;
        QStringList qsl = ld.split(":");
        // qDebug()<<ld.count()<<"Time"<<ld;
        if (qsl.count()==3)
        {

            ctime = qsl[0].toInt() *60 *60;

            ctime += qsl[1].toInt()  *60;
            ctime +=qsl[2].toDouble() ;

            qDebug()<<"Duration"<<qsl[0]<<qsl[1]<<qsl[2]<<"l= "<<length;

            ui->progressBar->setValue((int)((ctime/length)*100.00));

            ui->p_lb->setText(QString::number((int)((ctime/length)*100.00))+"%");


        }

    }



}
void ffprocessobj::startprocess()
{
    Status = "running";

    this->setWindowTitle("ffmpeg "+process_list.join(" "));
    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(process_stdout()));
    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(process_stdout()));
    connect(process , SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(process_completed(int, QProcess::ExitStatus)));
    QStringList L;
    foreach(QString s ,process_list )
    {
        s.remove('"'); //QProcess uses quotes in process args?
        L.append(s);

    }
    process->start(ffmpeglocation+"/ffmpeg",L,QIODevice::ReadWrite);
    timer->start();
    process->setReadChannel(QProcess::ProcessChannel::StandardOutput);
    ui->command_tb->append(args);
}
void ffprocessobj::process_completed(int ec , QProcess::ExitStatus es)
{

    if(ec==0 && es==0)
        Status = "completed ";
    else
    {
        Status = "error ";
    }
    emit finished();
    ui->progressBar->setValue(100);
    ui->p_lb->setText(QString::number(100)+"%");
    double time=  timer->elapsed()/1000.0;

    QMessageBox msgBox;
    if(ec==0 && es==0)
        ui->status_lb->setText("Process Complete in "+QString::number( time)+"seconds");
    else {
        ui->status_lb->setText("Process Failed --- Error");
    }

    //ffstdout->close();

    ui->killclose_btn->setText("Close");




}
void ffprocessobj::closeEvent( QCloseEvent* event )
{
    emit closing();
    event->accept();
}

void ffprocessobj::on_killclose_btn_clicked()
{
    if( process->state() == QProcess::Running)
        process->kill();
    else {
        this->close();
    }


}

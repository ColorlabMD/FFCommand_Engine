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



#include "qfe_window.h"
#include "ui_qfe_window.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStandardPaths>

QString getResourcesPath()
{
#if defined(Q_OS_WIN)
    return QCoreApplication::applicationDirPath() + "/";
#elif defined(Q_OS_OSX)
   return QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0]; //return QCoreApplication::applicationDirPath() + "/../Resources/";
#elif defined(Q_OS_LINUX)
    return QCoreApplication::applicationDirPath() + "/../share/yourapplication/";
#else
    return QCoreApplication::applicationDirPath() + "/";
#endif
}

QFE_Window::QFE_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFE_Window)
{
    ui->setupUi(this);
if (!QDir(getResourcesPath()).exists())
     {
    QDir().mkdir(getResourcesPath());
     QDir().mkdir(getResourcesPath()+"/Presets");
     QFile::copy(QCoreApplication::applicationDirPath() + "/../Resources/ffmpeglocation.txt", getResourcesPath()+"/ffmpeglocation.txt");
         QFile::copy(QCoreApplication::applicationDirPath() + "/../Resources/Presets/ffmprovisr.txt", getResourcesPath()+"/Presets/ffmprovisr.txt");
         QFile::copy(QCoreApplication::applicationDirPath() + "/../Resources/Presets/user.txt", getResourcesPath()+"/Presets/user.txt");



}
      qDebug()<<getResourcesPath();
    ui->param_table->setSelectionBehavior(ui->param_table->SelectRows);
    ui->param_table->setSelectionMode(ui->param_table->SingleSelection);
    ui->param_table->setDragDropMode(ui->param_table->InternalMove);
    ui->param_table->setDragDropOverwriteMode(false);



    ui->file_table->setSelectionBehavior(ui->param_table->SelectRows);
    ui->file_table->setSelectionMode(ui->param_table->SingleSelection);
    ui->file_table->setDragDropMode(ui->param_table->InternalMove);
     ui->file_table->setDropIndicatorShown(true);
    ui->file_table->setDragDropOverwriteMode(false);


probefilename=" ";

    OutputFileForm  * newout =   new OutputFileForm();
    connect(newout,SIGNAL(updateneeded()),this,SLOT(generate_ffmpeg_command()));
    ffoutputs.append(newout);
    ui->outputs_tw->insertTab( ui->outputs_tw->currentIndex()+1,newout,"Output"+QString::number(ui->outputs_tw->currentIndex()+1));
    pq = new processqueueDialog();
    connect(pq,SIGNAL(requestclear()),this,SLOT(queueclearrequest()));
    connect(pq,SIGNAL(queuestatechange()),this,SLOT(queuestatechanged()));
    QFile filepc(getResourcesPath()+"/"+"ffmpeglocation.txt");
    if(!filepc.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", filepc.errorString());
    }
    QTextStream in(&filepc);
    ffmpeglocation =  in.readLine();



    loadpresetmenu();



    //qDebug()<<getResourcesPath();

}


void QFE_Window::closeEvent (QCloseEvent *event)
{

bool anyrunning=false;
    foreach (ffprocessobj* d, ffinstances)
    {

        if (d->Status=="running")
anyrunning=true;

    }

    if (anyrunning)
    {
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "ffcommand engine",
                                                                tr("There are processes running, are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();

        pq->close();
        foreach (ffprocessobj* d, ffinstances)
        {

            d->close();


        }
    }

    }
    else

    {

        pq->close();
        foreach (ffprocessobj* d, ffinstances)
        {

            d->close();


        }

    }
}






void QFE_Window::loadpresetmenu()
{
    ui->menuPresets->clear();
    QDir directory(getResourcesPath()+"/Presets");
    QStringList psets = directory.entryList(QStringList() << "*.txt",QDir::Files);
    foreach(QString filename, psets) {
        //do whatever you need to do

        //********************************** Start Menu
        QFile filep(directory.path()+"/"+filename);

        if(!filep.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", filep.errorString());
        }
        QMenu *ffmproviser = new QMenu();
        ffmproviser->setTitle(filename.mid(0,filename.length()-4));
        QTextStream in(&filep);
        QString Comment;
        while(!in.atEnd()) {
            QString line = in.readLine();
            if (line[0]=='#')
            {
                QStringList pset;
                pset.append(line);
                pset.append(in.readLine());

                presets.append(pset);
                ffmproviser->addAction(pset[0],this,&QFE_Window::load_preset);
            }
            else
            {

               // qDebug()<<"Command";
            }
        }



        ui->menuPresets->addMenu(ffmproviser);
        //**********************************

    }






}
QFE_Window::~QFE_Window()
{
    delete ui;
}
void QFE_Window::process_stdout()
{








}

QList<int>  QFE_Window::getfileinputs()
{

int x=0;
QList<int> infilerows;
    for(int i=0; i<ui->file_table->rowCount();i++)
    {

        if (ui->file_table->item(i,1))
           {

            if (ui->file_table->item(i,1)->text() == "-i")
                infilerows.append(i);

        }

    }


    return  infilerows;



}
void QFE_Window:: load_preset()
{
    ui->batch_cb->setChecked(false);
    on_reset_btn_clicked();
    QAction* pAction = (QAction* )sender();
    foreach (QStringList sl ,presets)
    {
        if (sl[0]==pAction->text())
        {  parsecommand(sl[1]);
            generate_ffmpeg_command();

          //  qDebug()<<pAction->text();
            break;
        }
    }



}
void QFE_Window:: process_completed(int, QProcess::ExitStatus)
{

    //  double time= ffmpeg_process->timer->elapsed()/1000.0;
    QMessageBox msgBox;
    //  msgBox.setWindowTitle("Process Complete in "+QString::number( time)+"seconds");
    //   msgBox.setText("The process has finished in "+QString::number( time)+"seconds");
    msgBox.setStandardButtons(QMessageBox::Ok);

    //ffstdout->setWindowTitle("Process Complete in "+QString::number( time)+"seconds");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

    //ffstdout->close();




}
void QFE_Window::processclosed()
{
    ffprocessobj* s= (ffprocessobj * ) sender();
    for (int i = 0;i<ffinstances.count();i++)
    {

        if (s==ffinstances[i])
        {
            delete s;
            ffinstances.removeAt(i);
            return;

        }

    }



}

void QFE_Window::on_execute_btn_clicked()
{
    if(!ui->batch_cb->isChecked())
    {
        generate_ffmpeg_command();
        ffprocessobj * t= new ffprocessobj();
        connect(t,SIGNAL(closing()),this,SLOT(processclosed()));
        connect(t,SIGNAL(finished()),this,SLOT(queueitemfinished()));

        t->ffmpeglocation=ffmpeglocation;
        t->process_list=ffmpeg_process_arg;

        //t->show();

        //t->startprocess(ffmpeg_process_arg);

        ffinstances.append(t);
        t->args=("ffmpeg "+ffmpeg_process_arg.join(" "));
        pq->show();

        pq->enqueue(ffinstances);
    }
    else {



for(int x=0; x< getfileinputs().count();x++)
        {
            generate_ffmpeg_command(x);
            ffprocessobj * t= new ffprocessobj();
            connect(t,SIGNAL(closing()),this,SLOT(processclosed()));
            connect(t,SIGNAL(finished()),this,SLOT(queueitemfinished()));

            t->ffmpeglocation=ffmpeglocation;
            t->process_list=ffmpeg_process_arg;

            //t->show();

            //t->startprocess(ffmpeg_process_arg);

            ffinstances.append(t);
            t->args=("ffmpeg "+ffmpeg_process_arg.join(" "));
            pq->show();

            pq->enqueue(ffinstances);




        }




    }










}
void QFE_Window::killprocess()
{

}


void QFE_Window::on_probe_btn_clicked()
{

   probefilename = QFileDialog::getOpenFileName(
                this,tr("Input File"),".","*.*");
    if(probefilename.isEmpty()) return;
    ffprobe_process = new QProcess();
    QStringList ffprobe_string = {probefilename,"-v","quiet","-print_format", "json","-show_format","-show_streams"};
    ffprobe_process->start(ffmpeglocation+"/ffprobe",ffprobe_string,QIODevice::ReadOnly);

    ffprobe_process->setReadChannel(QProcess::ProcessChannel::StandardOutput);
    //ui->ffpcommand_le->setText("ffprobe "+ ffprobe_string.join(" "));
    QByteArray ba;
    if (ffprobe_process->waitForStarted(-1)) {
        while(ffprobe_process->waitForReadyRead(-1)) {
            ba += ffprobe_process->readAllStandardOutput();
        }
    }
    QString  probe_string = QString::fromUtf8(ba.data());

    ui->ProbeOutput_tb->setText(probe_string);
    //qDebug()<<probe_string;

    ffprobe_process->close();



    if (!probe_string.isEmpty()) {

        QJsonModel *newModel = new QJsonModel;

        ui->treeView->setModel(newModel);
        newModel->loadJson(ba);
        //  delete model;





    }
}

void QFE_Window::on_add_param_btn_clicked()
{
    ui->param_table->insertRow(0);

    QTableWidgetItem *newItem1 = new QTableWidgetItem(QString());
    QTableWidgetItem *newItem2 = new QTableWidgetItem(QString());

    ui->param_table->setItem(0,0,newItem1);
    ui->param_table->setItem(0,1,newItem2);
    generate_ffmpeg_command();

}
void QFE_Window::on_add_inputfiles_btn_clicked()
{

    QStringList filenames = QFileDialog::getOpenFileNames(
                this,tr("Input Files"),".","*.*");
    if(filenames.count()==0) return;
    foreach(QString s ,filenames)
    { int rowadd = ui->file_table->rowCount();


        ui->file_table->insertRow(rowadd);

        QTableWidgetItem *newItem1 = new QTableWidgetItem(QString("-i"));
        QTableWidgetItem *newItem2 = new QTableWidgetItem(QString(s));

        QPushButton* fnme = new QPushButton();

        connect(fnme,SIGNAL(clicked()),this,SLOT(on_add_input_filedlg_clicked()));
        const QSize BUTTON_SIZE = QSize(70, 22);
        fnme->setText("...");
        //QTableWidgetItem *newItem2 = new QTableWidgetItem(filename);
        ui->file_table->setItem(rowadd,1,newItem1);
        ui->file_table->setItem(rowadd,2,newItem2);
        ui->file_table->setCellWidget(rowadd,0,fnme);
        fnme->setMinimumSize(BUTTON_SIZE);
        fnme->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);


        fnme->setMinimumSize( BUTTON_SIZE );
        fnme->setMaximumSize( BUTTON_SIZE );}
    generate_ffmpeg_command();

}
void QFE_Window::on_add_input_btn_clicked()
{


    int rowadd = ui->file_table->rowCount();


    ui->file_table->insertRow(rowadd);

    QTableWidgetItem *newItem1 = new QTableWidgetItem(QString("-i"));
    QTableWidgetItem *newItem2 = new QTableWidgetItem(QString());


    QTableWidgetItem *newItem = new QTableWidgetItem(QString());
    ui->file_table->setItem(rowadd,1,newItem1);
    ui->file_table->setItem(rowadd,2,newItem2);
    ui->file_table->setItem(rowadd,0,newItem);

    generate_ffmpeg_command();
}
void QFE_Window::on_add_input_filedlg_clicked()
{

    QPushButton* sndr= (QPushButton *)sender();
    //qDebug()<<sndr;
    int rownum=0;
    for (int i = 0; i<ui->file_table->rowCount(); i++)
    {
        //  qDebug()<<ui->file_table->cellWidget(0,i);
        if (ui->file_table->cellWidget(i,0)==sndr)
            rownum=i;

    }
    QString filename = QFileDialog::getOpenFileName(
                this,tr("Input File"),".","*.*");
    if(filename.isEmpty()) return;
    QTableWidgetItem *newItem2 = new QTableWidgetItem(QString(filename));

    ui->file_table->setItem(rownum,2,newItem2);

    generate_ffmpeg_command();


}
void QFE_Window::generate_ffmpeg_command()
{
    ffmpeg_process_arg.clear();
    QString p;
    QString r;
    QString inputfname;
    //************************  input file variables
    if (ui->Overwrite_cb->isChecked())
        ffmpeg_process_arg.insert(0,"-y");
    if(!ui->batch_cb->isChecked())
    {
        for(int i=0; i<ui->file_table->rowCount();i++)
        {

            if (ui->file_table->item(i,1))
                p= ui->file_table->item(i,1)->text();
            if (ui->file_table->item(i,2))
                r= ui->file_table->item(i,2)->text();
            ffmpeg_process_arg.append(p);
            ffmpeg_process_arg.append(r);
        }
    }
    else {

        if (ui->file_table->item(0,1))
            p= ui->file_table->item(0,1)->text();
        if (ui->file_table->item(0,2))
            r= ui->file_table->item(0,2)->text();
        ffmpeg_process_arg.append(p);
        ffmpeg_process_arg.append(r);
        inputfname=r;

    }
    //************************  global process variables
    for(int i=0; i<ui->param_table->rowCount();i++)
    {

        if (ui->param_table->item(i,0))
            p= ui->param_table->item(i,0)->text();
        if (ui->param_table->item(i,1))
            r= ui->param_table->item(i,1)->text();
        ffmpeg_process_arg.append(p);
        ffmpeg_process_arg.append(r);
    }


    //************************  per output process variables


    for(int f=0; f<ffoutputs.count();f++)
    {
        QStringList opf= ffoutputs[f]->outputstringlist();
        opf.removeAll(QString(""));
        ffmpeg_process_arg.append(opf);
        if (ffoutputs[f]->batchmode)
        {
            QString fn= ffoutputs[f]->OutputDir+"/";
            fn+=inputfname.split("/").last();
            fn.remove(fn.length()-4,4);
            fn+=ffoutputs[f]->OutputFilename;
            ffmpeg_process_arg.append(fn);
        }
        else {
            ffmpeg_process_arg.append(ffoutputs[f]->OutputFilename);
            //qDebug()<<ffoutputs[f]->OutputFilename;
        }

    }


    ui->ffcommand_tb->clear();
    ui->ffcommand_tb->append("ffmpeg "+ffmpeg_process_arg.join(" "));
}

void QFE_Window::generate_ffmpeg_command(int innumber)
{
    ffmpeg_process_arg.clear();
    QString p;
    QString r;
    QString inputfname;
    //************************  input file variables




    if (ui->Overwrite_cb->isChecked())
        ffmpeg_process_arg.insert(0,"-y");


       getfileinputs();

// There is a better way to do this
        QList<int> inputfilerows= getfileinputs();
        for(int i=0; i<ui->file_table->rowCount()-inputfilerows.count();i++)
        {

            if (ui->file_table->item(i,1))
                p= ui->file_table->item(i,1)->text();
            if (ui->file_table->item(i,2))
                r= ui->file_table->item(i,2)->text();
            ffmpeg_process_arg.append(p);
            ffmpeg_process_arg.append(r);
        }
        if (ui->file_table->item(inputfilerows[innumber],1))
            p= ui->file_table->item(inputfilerows[innumber],1)->text();
        if (ui->file_table->item(inputfilerows[innumber],2))
            r= ui->file_table->item(inputfilerows[innumber],2)->text();
        ffmpeg_process_arg.append(p);
        ffmpeg_process_arg.append(r);
        inputfname=r;


    //************************  global process variables
    for(int i=0; i<ui->param_table->rowCount();i++)
    {

        if (ui->param_table->item(i,1))
            p= ui->param_table->item(i,0)->text();
        if (ui->param_table->item(i,2))
            r= ui->param_table->item(i,1)->text();
        ffmpeg_process_arg.append(p);
        ffmpeg_process_arg.append(r);
    }


    //************************  per output process variables


    for(int f=0; f<ffoutputs.count();f++)
    {
        QStringList opf= ffoutputs[f]->outputstringlist();
        opf.removeAll(QString(""));
        ffmpeg_process_arg.append(opf);
        if (ffoutputs[f]->batchmode)
        {
            QString fn= ffoutputs[f]->OutputDir+"/";
            fn+=inputfname.split("/").last();
            fn.remove(fn.length()-4,4);
            fn+=ffoutputs[f]->OutputFilename;
            ffmpeg_process_arg.append(fn);
        }
        else {
            ffmpeg_process_arg.append(ffoutputs[f]->OutputFilename);
        }

    }


    ui->ffcommand_tb->clear();
    ui->ffcommand_tb->append("ffmpeg "+ffmpeg_process_arg.join(" "));
}

void QFE_Window::on_file_table_cellClicked(int row, int column)
{

}

void QFE_Window::on_add_output_btn_clicked()
{

    OutputFileForm  * newout =   new OutputFileForm();

    connect(newout,SIGNAL(updateneeded()),this,SLOT(generate_ffmpeg_command()));
    ffoutputs.append(newout);
    if(ui->batch_cb->isChecked())
    {

        newout->setforbatch(true);



    }
    else {

        newout->setforbatch(false);



    }

    ui->outputs_tw->insertTab(ffoutputs.length()-1,newout,"Output"+QString::number(ffoutputs.length()-1));


}
void QFE_Window::parsecommand(QString incommand)
{
    QString commandinput= incommand;
    QStringList commandparts;
    // store dialog content somewhere
    //qDebug()<<commandinput;


    QStringList tmpList = commandinput.split(QRegExp("\"")); // Split by "
    bool inside = false;
    commandparts.clear();
    foreach (QString s, tmpList) {
        if (inside) { // If 's' is inside quotes ...
            s.insert(0,"\"");
            s.append("\"");
            commandparts.append(s); // ... get the whole string
        } else { // If 's' is outside quotes ...
            commandparts.append(s.split(QRegExp("\\s+"), QString::SkipEmptyParts)); // ... get the splitted string
        }
        inside = !inside;
    }

  bool inputformatter =true;
  int inputendix=commandparts.lastIndexOf("-i");
  //qDebug()<<"last input index: "<<inputendix;
    int arginc=1;
    while(arginc<commandparts.count())
    {

        if (commandparts[arginc]=="-i" || arginc < inputendix)
        {

             if (commandparts[arginc]=="-y")
            {
                ui->Overwrite_cb->setChecked(true);


            }
             else {


            int rowadd = ui->file_table->rowCount();
            ui->file_table->insertRow(rowadd);

            QTableWidgetItem *newItem1 = new QTableWidgetItem(QString(commandparts[arginc]));
            QTableWidgetItem *newItem2 ;
            if (commandparts[arginc+1].at(0)=='-')
            newItem2 = new QTableWidgetItem(QString());
             else
            {
            arginc++;
            newItem2 = new QTableWidgetItem(QString(commandparts[arginc]));
}



            QTableWidgetItem *newItem = new QTableWidgetItem(QString());

            ui->file_table->setItem(rowadd,1,newItem1);
            ui->file_table->setItem(rowadd,2,newItem2);
             ui->file_table->setItem(rowadd,0,newItem);

}


        }
        else if (commandparts[arginc]=="-an" ||commandparts[arginc]== "-vn"||commandparts[arginc]== "-dn")
        {
            ffoutputs[ui->outputs_tw->currentIndex()]->addrow(commandparts[arginc],QString());

        }
        else if (commandparts[arginc]=="-y")
        {
            ui->Overwrite_cb->setChecked(true);

        }
        else if (commandparts[arginc].at(0)=='-')
        {
            QString t;
            if (arginc ==commandparts.count()-1)
            ffoutputs[ui->outputs_tw->currentIndex()]->setoutputfilename(commandparts[arginc]);
            else if (commandparts[arginc+1].at(0)=='-')


                ffoutputs[ui->outputs_tw->currentIndex()]->addrow(commandparts[arginc],t);
            else
            {
                ffoutputs[ui->outputs_tw->currentIndex()]->addrow(commandparts[arginc],commandparts[arginc+1]);
                arginc++;
            }

        }
        else if (!commandparts[arginc].isEmpty())
        {

            ffoutputs[ui->outputs_tw->currentIndex()]->setoutputfilename(commandparts[arginc]);
            if (arginc+1!=commandparts.count())
            {
                on_add_output_btn_clicked();
                ui->outputs_tw->setCurrentIndex( ui->outputs_tw->currentIndex()+1);
            }

        }

        arginc++;
    }

    // generate_ffmpeg_command();


}
void QFE_Window::on_ffparse_btn_clicked()
{


    parsecommandDialog* t =new parsecommandDialog();



    if (t->exec() == QDialog::Accepted)
    {
        on_reset_btn_clicked();
        parsecommand(t->FFCommand);

        generate_ffmpeg_command();
    }

}

void QFE_Window::on_file_table_cellDoubleClicked(int row, int column)
{if (column==1)
    {



    }

}

void QFE_Window::on_file_table_cellChanged(int row, int column)
{
    if(!ui->file_table->cellWidget(row,0))
    {
     QPushButton* fnme = new QPushButton();

    connect(fnme,SIGNAL(clicked()),this,SLOT(on_add_input_filedlg_clicked()));
    const QSize BUTTON_SIZE = QSize(22, 22);
     fnme->setText("...");
    ui->file_table->setCellWidget(row,0,fnme);
    fnme->setMinimumSize(BUTTON_SIZE);
    fnme->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
}

//    fnme->setMinimumSize( BUTTON_SIZE );
   // fnme->setMaximumSize( BUTTON_SIZE );


    generate_ffmpeg_command();
}

void QFE_Window::on_delete_output_btn_clicked()
{
    if (ui->outputs_tw->count()>0)
    {
        int idf =  ui->outputs_tw->currentIndex();

        ui->outputs_tw->removeTab( idf);
        delete ffoutputs[idf];
        ffoutputs.removeAt(idf);
    }
    \
}

void QFE_Window::on_reset_btn_clicked()
{
    ui->batch_cb->setChecked(false);
    while (ui->outputs_tw->count()>0)
    {

        foreach (OutputFileForm * s, ffoutputs)
        {
            int idf = ui->outputs_tw->count()-1;
            ui->outputs_tw->removeTab( idf);
            delete ffoutputs[idf];
            ffoutputs.removeAt(idf);

        }



    }
    OutputFileForm  * newout =   new OutputFileForm();

    connect(newout,SIGNAL(updateneeded()),this,SLOT(generate_ffmpeg_command()));
    ffoutputs.append(newout);
    ui->outputs_tw->insertTab(ffoutputs.length()-1,newout,"Output"+QString::number(ffoutputs.length()-1));


    int incount = ui->file_table->rowCount();
    for ( int k = 0; k<incount; k++)
    {
        ui->file_table->removeRow( 0);

    }

}

void QFE_Window::on_del_input_btn_clicked()
{
    ui->file_table->removeRow(  ui->file_table->currentRow());
}


void QFE_Window::on_kill_all_btn_clicked()
{


    //   if (ffmpeg_process->process->state() == QProcess::Running)
    //      ffmpeg_process->process->kill();
}

void QFE_Window::on_save_pset_btn_clicked()
{
    PresetSaveDialog* t =new PresetSaveDialog();
    QDir directory(getResourcesPath()+"/Presets");
    QStringList psets = directory.entryList(QStringList() << "*.txt",QDir::Files);
    t->setup(psets);

    if (t->exec() == QDialog::Accepted)
    {


        generate_ffmpeg_command();
        QFile filepc(getResourcesPath()+"/Presets/"+t->file);
        filepc.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
        if(!filepc.open(QIODevice::Append)) {
            QMessageBox::information(0, "error", filepc.errorString());
        }
        QTextStream out(&filepc);
        out<<t->comment<<endl;
        generate_ffmpeg_command();
        out<<"ffmpeg "+ffmpeg_process_arg.join(" ")<<endl;
        filepc.close();

    }

    loadpresetmenu();
}
int QFE_Window::getactiveinstances()

{
    int activeinstancecount =0;
    for (int i = 0;i<ffinstances.count();i++)
    {

        if (ffinstances[i]->Status == "running")
        {
            activeinstancecount++;

        }

    }
    return activeinstancecount;
}
QList<ffprocessobj  *> QFE_Window::getqueudinstances()

{
    QList<ffprocessobj  *> tld;
    int activeinstancecount =0;
    for (int i = 0;i<ffinstances.count();i++)
    {

        if (ffinstances[i]->Status == "queued")
        {
            tld.append(ffinstances[i]);

        }

    }
    return tld;
}
void QFE_Window::queuestatechanged()
{





    QList<ffprocessobj  *> d;

    if (pq->running)
    {
        QList<ffprocessobj  *> d = getqueudinstances();

        while(d.count() > 0  && (getactiveinstances()<ui->maxinstance_sb->value()) )
        {
            //qDebug()<<getactiveinstances();
            d[0]->startprocess();
            d[0]->show();
            d.removeAt(0);

        }
    }
    else {

    }
    pq->enqueue(ffinstances);

}
void QFE_Window::queueclearrequest()
{


    foreach(ffprocessobj * s ,ffinstances)
    {
        if (s->Status== "queued" ||s->Status=="completed" )
            ffinstances.removeOne(s);

    }
    pq->enqueue(ffinstances);

}
void QFE_Window::on_showqueue_btn_clicked()
{
    pq->show();

}
void QFE_Window::queueitemfinished()
{
    pq->enqueue(ffinstances);
    if (pq->running)
    {
        QList<ffprocessobj  *> d = getqueudinstances();

        while(d.count() > 0  && (getactiveinstances()<ui->maxinstance_sb->value()) )
        {
            //qDebug()<<getactiveinstances();
            d[0]->startprocess();
            d[0]->show();
            d.removeAt(0);

        }
        if(d.count()==0)
            pq->stopqueue();
    }
    pq->enqueue(ffinstances);
}

void QFE_Window::on_actionSet_FFmpeg_Dir_triggered()
{

    ffmpegbinaryDialog d;
    d.setup(ffmpeglocation);

    if (d.exec() == QDialog::Accepted)
    {
        ffmpeglocation=d.location;
        QFile filepc(getResourcesPath()+"/"+"ffmpeglocation.txt");
        filepc.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
        if(!filepc.open(QIODevice::WriteOnly)) {
            QMessageBox::information(0, "error", filepc.errorString());
        }
        QTextStream out(&filepc);
        out<< ffmpeglocation;
        filepc.close();

    }

}

void QFE_Window::on_del_param_btn_clicked()
{
    ui->param_table->removeRow(  ui->param_table->currentRow());
        generate_ffmpeg_command();
}

void QFE_Window::on_param_table_cellChanged(int row, int column)
{
    generate_ffmpeg_command();
}



void QFE_Window::on_batch_cb_clicked()
{
    if(ui->batch_cb->isChecked())
    {
        for(int f=0; f<ffoutputs.count();f++)
        {
            ffoutputs[f]->setforbatch(true);


        }
    }
    else {
        for(int f=0; f<ffoutputs.count();f++)
        {
            ffoutputs[f]->setforbatch(false);


        }
    }


    generate_ffmpeg_command();

}

void QFE_Window::on_batch_cb_stateChanged(int arg1)
{

    generate_ffmpeg_command();
}

void QFE_Window::on_Overwrite_cb_clicked()
{
    generate_ffmpeg_command();
}


void QFE_Window::on_actionAbout_FFCommand_Engine_triggered()
{
    aboutDialog n;

    n.exec();

}

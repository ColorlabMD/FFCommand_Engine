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


#ifndef QFE_WINDOW_H
#define QFE_WINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDomDocument>
#include <QTreeView>
#include <QMenuBar>
#include <QFileDialog>

#include "qjsonmodel.h"
#include <QStandardItemModel>
#include "outputfileform.h"
#include "ffmpegarg.h"
#include "parsecommanddialog.h"
#include "ffprocessobj.h"
#include "presetsavedialog.h"
#include "processqueuedialog.h"
#include "ffmpegbinarydialog.h"
#include "aboutdialog.h"
namespace Ui {
class QFE_Window;
}

class QFE_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit QFE_Window(QWidget *parent = nullptr);
    void XMLParser(QString xmlqs);

    void parsecommand(QString incommand);
    void closeEvent(QCloseEvent * event);
    ~QFE_Window();
    int getactiveinstances();
    QList<ffprocessobj  *> getqueudinstances();
public slots:
    void generate_ffmpeg_command();
    void generate_ffmpeg_command(int);
    void process_stdout();
    void process_completed(int, QProcess::ExitStatus);
    void killprocess();
    void load_preset();
    void loadpresetmenu();
    void queuestatechanged(); //from queue dialog
    void queueclearrequest(); //from queue dialog
    void queueitemfinished();//from proc object
    QList<int> getfileinputs();
private slots:
    void on_execute_btn_clicked();


    void processclosed();

    void on_probe_btn_clicked();

    void on_add_param_btn_clicked();

    void on_add_input_btn_clicked();
    void on_add_input_filedlg_clicked();

    void on_file_table_cellClicked(int row, int column);

    void on_add_output_btn_clicked();

    void on_ffparse_btn_clicked();

    void on_file_table_cellDoubleClicked(int row, int column);

    void on_file_table_cellChanged(int row, int column);

    void on_delete_output_btn_clicked();

    void on_reset_btn_clicked();

    void on_del_input_btn_clicked();

    void on_kill_all_btn_clicked();

    void on_save_pset_btn_clicked();

    void on_showqueue_btn_clicked();


    void on_actionSet_FFmpeg_Dir_triggered();

    void on_del_param_btn_clicked();

    void on_param_table_cellChanged(int row, int column);

    void on_add_inputfiles_btn_clicked();

    void on_batch_cb_clicked();

    void on_batch_cb_stateChanged(int arg1);

    void on_Overwrite_cb_clicked();


    void on_actionAbout_FFCommand_Engine_triggered();

private:
    Ui::QFE_Window *ui;
    QString ffmpeglocation;
QString probefilename;
    QStringList ffmpeg_process_arg;
   // QList < ffcommand>  ffcommandinput_list;  later tables will keep data for now
   // QList < ffcommand>  ffcommandglobal_list;  later tables will keep data for now
    QProcess* ffprobe_process;
    QStringList ffprobe_process_arg;
    QJsonModel *model;
    QStandardItemModel *qsmodel;

    QString FinalCommand;

    QList <OutputFileForm *> ffoutputs;

    QList <ffprocessobj*> ffinstances;
    processqueueDialog * pq;
    QList <QStringList> presets;
    ffprocessobj * ffprocobj = NULL;

};

#endif // QFE_WINDOW_H

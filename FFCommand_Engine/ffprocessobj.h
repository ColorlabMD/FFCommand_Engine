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


#ifndef FFPROCESSOBJ_H
#define FFPROCESSOBJ_H
#include <QWindow>
#include <QDialog>
#include <QElapsedTimer>
#include <QProcess>

namespace Ui {
class ffprocessobj;
}

class ffprocessobj : public QDialog
{
    Q_OBJECT

public:
    explicit ffprocessobj(QWidget *parent = nullptr);
    ~ffprocessobj();
    void startprocess();
void closeEvent( QCloseEvent* event );
    QElapsedTimer *timer;
    QProcess *process;
     QString args;
     QStringList process_list;
     QString Status;
     QString ffmpeglocation;
double length;

public slots:
     void process_stdout();
       void process_completed(int, QProcess::ExitStatus);
  signals:
       void closing();
       void finished();
private slots:
       void on_killclose_btn_clicked();

private:
    Ui::ffprocessobj *ui;
};

#endif // FFPROCESSOBJ_H

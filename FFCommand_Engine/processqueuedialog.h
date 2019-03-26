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

#ifndef PROCESSQUEUEDIALOG_H
#define PROCESSQUEUEDIALOG_H

#include <QDialog>
#include "ffprocessobj.h"
#include <QQueue>
#include <QList>
namespace Ui {
class processqueueDialog;
}

class processqueueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit processqueueDialog(QWidget *parent = nullptr);
    ~processqueueDialog();
    void enqueue(QList<ffprocessobj *> );
    //QQueue <ffprocessobj*> processq;
void stopqueue();

    bool running;
private slots:
    void on_startstop_btn_clicked();

    void on_clear_btn_clicked();
signals:
    void queuestatechange();
    void requestclear();
private:
    Ui::processqueueDialog *ui;
};

#endif // PROCESSQUEUEDIALOG_H

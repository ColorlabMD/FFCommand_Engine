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

#ifndef QFETABLEWIDGET_H

#define QFETABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QDropEvent>
class QFETableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit QFETableWidget(QWidget *parent = nullptr);
    void dropEvent(QDropEvent *event)Q_DECL_OVERRIDE;
signals:


public slots:
};

#endif // QFETABLEWIDGET_H

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



#include "qfetablewidget.h"
//for proper drag and drop reording
QFETableWidget::QFETableWidget(QWidget *parent) : QTableWidget(parent)
{

}
void QFETableWidget::dropEvent(QDropEvent *event)
{

    if(event->source() == this)
    {
        int newRow = this->indexAt(event->pos()).row();
        QTableWidgetItem *selectedItem;
        QList<QTableWidgetItem*> selectedItems = this->selectedItems();


        if(newRow == -1)
            newRow = this->rowCount();
        int i;
        for(i = 0; i < (selectedItems.length())/this->columnCount(); i++)
        {
            this->insertRow(newRow);
        }
        int currentOldRow = -1;
        int currentNewRow = newRow-1;
        QList<int> deleteRows;
        foreach(selectedItem, selectedItems)
        {
            int column = selectedItem->column();
            if(selectedItem->row() != currentOldRow)
            {
                currentOldRow = selectedItem->row();
                deleteRows.append(currentOldRow);
                currentNewRow++;
            }

            this->takeItem(currentOldRow, column);
            this->setItem(currentNewRow, column, selectedItem);
        }

        for(i = deleteRows.count()-1; i>=0; i--)
        {
            this->removeRow(deleteRows.at(i));
        }

    }
}

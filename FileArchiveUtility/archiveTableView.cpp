/* 
 * File:   archiveTableView.cpp
 * Author: lee
 * 
 * Created on 30 September 2015, 1:28 PM
 */

#include "archiveTableView.h"

archiveTableView::archiveTableView(QObject* parent) : QAbstractTableModel(parent) {
}

QVariant archiveTableView::data(const QModelIndex &index, int role) const {
    if (role==Qt::DisplayRole){
        if (index.column()==0){
            return QString(recordsCollection->at(index.row()).getVersionNumber());
        }
        if (index.column()==1){
            return QString((int)recordsCollection->at(index.row()).getModifyTime().tv_sec);
        }
        if (index.column()==2){
            return QString(recordsCollection->at(index.row()).getLength());
        }
    }
    return QVariant();
}

QVariant archiveTableView::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role==Qt::DisplayRole){
        if (orientation==Qt::Horizontal){
            //std::cout << "In headerdata" << std::endl;
            switch(section){
                case 0:
                    return QString("Version #");
                case 1:
                    return QString("Date");
                case 2:
                    return QString("Size");
            }
        }
    }
    return QVariant();
}

bool archiveTableView::setData(const QModelIndex&, const QVariant&, int){
    return false;
}

bool archiveTableView::insertRows(int, int, const QModelIndex&){
    return true;
}

bool archiveTableView::removeRows(int, int, const QModelIndex&){
    return true;
}

archiveTableView::~archiveTableView() {
}


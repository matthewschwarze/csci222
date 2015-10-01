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
    //displays the data in the table
    if (role==Qt::DisplayRole){
        if (index.column()==0){
            std::ostringstream ss;
            ss << (recordsCollection->at(index.row()).getVersionNumber());
            QString tempStr(ss.str().c_str());
            return tempStr;
        }
        if (index.column()==1){
            std::ostringstream ss;
            QDateTime timestamp;
            timestamp.setTime_t(recordsCollection->at(index.row()).getModifyTime().tv_sec);
            ss << (timestamp.toString().toStdString());
            QString tempStr(ss.str().c_str());
            return tempStr;
        }
        if (index.column()==2){
            std::ostringstream ss;
            ss << (recordsCollection->at(index.row()).getLength());
            QString tempStr(ss.str().c_str());
            return tempStr;
        }
    }
    return QVariant();
}

QVariant archiveTableView::headerData(int section, Qt::Orientation orientation, int role) const{
    //displays the headers
    if (role==Qt::DisplayRole){
        if (orientation==Qt::Horizontal){
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


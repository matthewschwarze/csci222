/* 
 * File:   archiveTableView.h
 * Author: lee
 *
 * Created on 30 September 2015, 1:28 PM
 */

#ifndef ARCHIVETABLEVIEW_H
#define	ARCHIVETABLEVIEW_H

#include <QAbstractTableModel>
#include <QtGui>
#include <vector>
#include <string>
#include <sstream>
#include <QDateTime>
#include "fileArchiver.h"
#include "VersionRec.h"

class archiveTableView : public QAbstractTableModel{
public:
    archiveTableView(QObject* parent);
    virtual ~archiveTableView();
    int rowCount(const QModelIndex& parent=QModelIndex()) const { return recordsCollection->size(); }
    int columnCount(const QModelIndex& parent=QModelIndex()) const { return 3; }
    void addTheData(std::vector<VersionRec> *data) { this->recordsCollection = data; }
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex& index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex& index=QModelIndex());
private:
    std::vector<VersionRec>* recordsCollection;
};

#endif	/* ARCHIVETABLEVIEW_H */


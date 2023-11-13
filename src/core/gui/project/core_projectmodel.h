/*
    Modbus Tools

    Created: 2023
    Author: Serhii Marchuk, https://github.com/serhmarch

    Copyright (C) 2023  Serhii Marchuk

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef CORE_PROJECTMODEL_H
#define CORE_PROJECTMODEL_H

#include <QAbstractItemModel>

#include <mbcore.h>

class mbCore;
class mbCoreProject;
class mbCorePort;

class MB_EXPORT mbCoreProjectModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    mbCoreProjectModel(QObject* parent = nullptr);

public:
    mbCoreProject *projectCore() const { return m_project; }

public: // table model interface
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

public: // settings
    inline bool useNameWithSettings() const { return m_settings.useNameWithSettings; }
    void setUseNameWithSettings(bool use);

public:
    QModelIndex portIndex(mbCorePort *port) const;
    mbCorePort *portCore(const QModelIndex &index) const;

protected Q_SLOTS:
    virtual void setProject(mbCoreProject *project);
    virtual void portAdd(mbCorePort *port);
    virtual void portRemove(mbCorePort *port);
    virtual void portChanged();

protected:
    mbCoreProject *m_project;
    struct
    {
        bool useNameWithSettings;
    } m_settings;
};

#endif // CORE_PROJECTMODEL_H

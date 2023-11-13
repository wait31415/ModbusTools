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
#include "client.h"

#include <iostream>

#include <QEventLoop>
#include <QDateTime>

#include <ModbusClient.h>
#include <project/client_project.h>
#include <project/client_port.h>
#include <project/client_device.h>
#include <project/client_dataview.h>
#include <project/client_builder.h>

#include <gui/client_ui.h>

#include <runtime/client_runtime.h>

mbClient::Strings::Strings() :
    settings_application(QStringLiteral("Client")),
    default_client(settings_application),
    default_conf_file(QStringLiteral("client.conf")),
    GUID(QStringLiteral("e9da9345-c8b1-47d0-acbd-0a3401fef700")) // generated by https://www.guidgenerator.com/online-guid-generator.aspx
{
}

const mbClient::Strings &mbClient::Strings::instance()
{
    static const Strings s;
    return s;
}


mbClient::mbClient() :
    mbCore (Strings::instance().settings_application)
{
}

mbClient::~mbClient()
{
}

void mbClient::sendMessage(mb::Client::DeviceHandle_t handle, const mbClientRunMessagePtr &message)
{
    runtime()->sendMessage(handle, message);
}

void mbClient::updateItem(mb::Client::ItemHandle_t handle, const QByteArray &data, Modbus::StatusCode status, mb::Timestamp_t timestamp)
{
    runtime()->updateItem(handle, data, status, timestamp);
}

void mbClient::writeItemData(mb::Client::ItemHandle_t handle, const QByteArray &data)
{
    runtime()->writeItemData(handle, data);
}

QString mbClient::createGUID()
{
    return Strings::instance().GUID;
}

mbCoreUi *mbClient::createUi()
{
    return new mbClientUi(this);
}

mbCoreProject *mbClient::createProject()
{
    mbClientProject *project = new mbClientProject;
    mbClientPort *port = new mbClientPort;
    project->portAdd(port);

    mbClientDevice *d = new mbClientDevice;
    project->deviceAdd(d);
    port->deviceAdd(d);

    mbClientDataView *wl = new mbClientDataView;
    project->dataViewAdd(wl);
    return project;
}

mbCoreBuilder *mbClient::createBuilder()
{
    return new mbClientBuilder;
}

mbCoreRuntime *mbClient::createRuntime()
{
    return new mbClientRuntime(this);
}



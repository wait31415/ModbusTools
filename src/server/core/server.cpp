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
#include "server.h"

#include <iostream>

#include <QEventLoop>

#include <project/server_project.h>
#include <project/server_builder.h>
#include <project/server_port.h>
#include <project/server_deviceref.h>

#include <gui/server_ui.h>

#include <runtime/server_runtime.h>

mbServer::Strings::Strings() :
    settings_application(QStringLiteral("Server")),
    default_server(settings_application),
    default_conf_file(QStringLiteral("server.conf")),
    GUID(QStringLiteral("bcde38bb-2402-4b3f-9ddb-3abfd0986852")) // generated by https://www.guidgenerator.com/online-guid-generator.aspx
{
}

const mbServer::Strings &mbServer::Strings::instance()
{
    static const Strings s;
    return s;
}

mbServer::mbServer() :
    mbCore(Strings::instance().settings_application)
{
    Strings s = Strings::instance();
}

mbServer::~mbServer()
{
}

QString mbServer::createGUID()
{
    return Strings::instance().GUID;
}

mbCoreUi *mbServer::createUi()
{
    return new mbServerUi(this);
}

mbCoreProject *mbServer::createProject()
{
    mbServerProject *p = new mbServerProject;
    mbServerDevice *d = new mbServerDevice;
    p->deviceAdd(d);

    mbServerDeviceRef *ref = new mbServerDeviceRef(d);
    mbServerPort *port = new mbServerPort;
    port->deviceAdd(ref);
    p->portAdd(port);
    return p;
}

mbCoreBuilder *mbServer::createBuilder()
{
    return new mbServerBuilder;
}

mbCoreRuntime *mbServer::createRuntime()
{
    return new mbServerRuntime(this);
}


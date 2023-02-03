//
//     Copyright (C) 2023 Mikel Johnson <mikel5764@gmail.com> 
//
//     This program is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.
// 
//     This library is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.
// 
//     You should have received a copy of the GNU Lesser General Public
//     License along with this library. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef VIEWNAV_H
#define VIEWNAV_H

#include <QObject>
#include "qmake/share_interface.h"

class ShareSender : public QObject
{
    Q_OBJECT
public:
    ShareSender();
    Q_INVOKABLE void send(QString mime, QString json);
    Q_INVOKABLE bool canShare(QString mime, QString json);

private:
    org::freedesktop::Share* m_shareSender;
};

#endif // VIEWNAV_H

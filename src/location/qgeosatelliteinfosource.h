/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QGEOSATELLITEINFOSOURCE_H
#define QGEOSATELLITEINFOSOURCE_H

#include <QtLocation/QGeoSatelliteInfo>

#include <QObject>
#include <QList>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE


class QGeoSatelliteInfoSourcePrivate;
class Q_LOCATION_EXPORT QGeoSatelliteInfoSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval)
    Q_PROPERTY(int minimumUpdateInterval READ minimumUpdateInterval)

public:
    enum Error {
        AccessError,
        ClosedError,              /* 1 */
        UnknownSourceError = -1
    };
    Q_ENUMS(Error)

    explicit QGeoSatelliteInfoSource(QObject *parent);
    virtual ~QGeoSatelliteInfoSource();

    static QGeoSatelliteInfoSource *createDefaultSource(QObject *parent);
    static QGeoSatelliteInfoSource *createSource(const QString &sourceName, QObject *parent);
    static QStringList availableSources();

    virtual void setUpdateInterval(int msec);
    int updateInterval() const;
    virtual int minimumUpdateInterval() const = 0;
    virtual Error error() const = 0;

public Q_SLOTS:
    virtual void startUpdates() = 0;
    virtual void stopUpdates() = 0;

    virtual void requestUpdate(int timeout = 0) = 0;

Q_SIGNALS:
    void satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &satellites);
    void satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &satellites);
    void requestTimeout();
    void error(QGeoSatelliteInfoSource::Error);

private:
    Q_DISABLE_COPY(QGeoSatelliteInfoSource)
    QGeoSatelliteInfoSourcePrivate *d;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif

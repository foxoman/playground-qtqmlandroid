/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt QML Android module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qnativeandroidalertdialog_p.h"
#include "qtqmlandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

QNativeAndroidAlertDialog::QNativeAndroidAlertDialog(QObject *parent) :
    QNativeAndroidDialog(parent)
{
}

QString QNativeAndroidAlertDialog::title() const
{
    return m_title;
}

void QNativeAndroidAlertDialog::setTitle(const QString &title)
{
    if (m_title != title) {
        m_title = title;
        QtQmlAndroid::callTextMethod(instance(), "setTitle", title);
        emit titleChanged();
    }
}

QString QNativeAndroidAlertDialog::message() const
{
    return m_message;
}

void QNativeAndroidAlertDialog::setMessage(const QString &message)
{
    if (m_message != message) {
        m_message = message;
        QtQmlAndroid::callTextMethod(instance(), "setMessage", message);
        emit messageChanged();
    }
}

QAndroidJniObject QNativeAndroidAlertDialog::onCreate()
{
    return QAndroidJniObject("android/app/AlertDialog",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QNativeAndroidAlertDialog::onInflate(QAndroidJniObject& instance)
{
    QNativeAndroidDialog::onInflate(instance);

    if (!m_title.isNull())
        instance.callMethod<void>("setTitle", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(m_title).object());
    if (!m_message.isNull())
        instance.callMethod<void>("setMessage", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(m_message).object());
}

QT_END_NAMESPACE
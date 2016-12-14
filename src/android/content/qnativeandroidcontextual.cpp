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

#include "qnativeandroidcontextual_p.h"
#include "qnativeandroidcontext_p.h"
#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE

QNativeAndroidContextual::QNativeAndroidContextual(QObject *parent) :
    QNativeAndroidObject(parent), m_context(0)
{
    if (!initContext())
        QMetaObject::invokeMethod(this, "resolveContext", Qt::QueuedConnection);
}

QNativeAndroidContextual::QNativeAndroidContextual(QNativeAndroidContext* context, QObject *parent) :
    QNativeAndroidObject(parent || context == this ? parent : context), m_context(0)
{
    if (!initContext(context))
        QMetaObject::invokeMethod(this, "resolveContext", Qt::QueuedConnection);
}

QAndroidJniObject QNativeAndroidContextual::ctx() const
{
    if (!m_context)
        return QAndroidJniObject();
    return m_context->instance();
}

QNativeAndroidContext *QNativeAndroidContextual::context() const
{
    return m_context;
}

void QNativeAndroidContextual::setContext(QNativeAndroidContext *context)
{
    if (m_context != context) {
        m_context = context;
        propagateContext();
        emit contextChanged();
    }
}

void QNativeAndroidContextual::componentComplete()
{
    QNativeAndroidObject::componentComplete();
    propagateContext();
}

static QNativeAndroidContext *findContext(QNativeAndroidObject *object)
{
    QNativeAndroidContext *context = qobject_cast<QNativeAndroidContext *>(object);
    QObject *p = object->parent();
    while (p && !context) {
        QNativeAndroidContextual *contextual = qobject_cast<QNativeAndroidContextual *>(p);
        if (contextual)
            context = contextual->context();
        p = p->parent();
    }
    return context;
}

bool QNativeAndroidContextual::initContext(QNativeAndroidContext *context)
{
    if (!context)
        context = findContext(this);
    setContext(context);
    return context;
}

void QNativeAndroidContextual::resolveContext()
{
    if (!m_context) {
        setContext(findContext(this));
        if (!m_context)
            qWarning() << "QNativeAndroidContextual: could not resolve context for" << this;
    }
}

void QNativeAndroidContextual::propagateContext()
{
    foreach (QObject *child, children()) {
        QNativeAndroidContextual *contextual = qobject_cast<QNativeAndroidContextual *>(child);
        if (contextual)
            contextual->setContext(m_context);
    }
}

QT_END_NAMESPACE

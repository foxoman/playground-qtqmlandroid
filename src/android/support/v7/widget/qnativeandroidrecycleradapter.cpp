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

#include "qnativeandroidrecycleradapter_p.h"
#include "qtqmlandroidfunctions_p.h"
#include "qnativeandroidview_p.h"
#include <QtQml/qqmlcomponent.h>
#include <QtQml/qqmlcontext.h>

QT_BEGIN_NAMESPACE

QNativeAndroidRecyclerAdapter::QNativeAndroidRecyclerAdapter(QObject *parent) :
    QNativeAndroidContextual(parent), m_count(0), m_delegate(0)
{
}

int QNativeAndroidRecyclerAdapter::count() const
{
    return m_count;
}

void QNativeAndroidRecyclerAdapter::setCount(int count)
{
    if (m_count != count) {
        m_count = count;
        QtQmlAndroid::callIntMethod(instance(), "setItemCount", count);
        emit countChanged();
    }
}

QQmlComponent *QNativeAndroidRecyclerAdapter::delegate() const
{
    return m_delegate;
}

void QNativeAndroidRecyclerAdapter::setDelegate(QQmlComponent *delegate)
{
    if (m_delegate != delegate) {
        m_delegate = delegate;
        QtQmlAndroid::callVoidMethod(instance(), "notifyDataSetChanged");
        emit delegateChanged();
    }
}

QAndroidJniObject QNativeAndroidRecyclerAdapter::onCreate()
{
    return QAndroidJniObject("qt/android/support/v7/widget/QtNativeRecyclerAdapter",
                             "(IJ)V",
                             m_count,
                             reinterpret_cast<jlong>(this));
}

void QNativeAndroidRecyclerAdapter::onInflate(QAndroidJniObject &instance)
{
    QNativeAndroidContextual::onInflate(instance);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        onRegisterNativeMethods(instance.object());
        nativeMethodsRegistered = true;
    }

    if (m_count > 0)
        instance.callMethod<void>("setItemCount", "(I)V", m_count);
}

void QNativeAndroidRecyclerAdapter::onRegisterNativeMethods(jobject adapter)
{
    JNINativeMethod methods[] {{"onCreateViewHolder", "(JLandroid/view/ViewGroup;I)Lqt/android/support/v7/widget/QtNativeRecyclerAdapter$ViewHolder;", reinterpret_cast<void *>(onCreateViewHolder)},
                               {"onBindViewHolder", "(JLqt/android/support/v7/widget/QtNativeRecyclerAdapter$ViewHolder;I)V", reinterpret_cast<void *>(onBindViewHolder)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(adapter);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

jobject QNativeAndroidRecyclerAdapter::onCreateViewHolder(JNIEnv *env, jobject object, jlong instance, jobject parent, jint viewType)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    Q_UNUSED(parent);
    Q_UNUSED(viewType);
    QNativeAndroidRecyclerAdapter *adapter = reinterpret_cast<QNativeAndroidRecyclerAdapter *>(instance);
    if (adapter) {
        QNativeAndroidView *item = nullptr;
        QMetaObject::invokeMethod(adapter, "createItem", Qt::BlockingQueuedConnection, Q_RETURN_ARG(QNativeAndroidView *, item));
        item->construct();
        adapter->m_holders += QAndroidJniObject("qt/android/support/v7/widget/QtNativeRecyclerAdapter$ViewHolder",
                                                "(Landroid/view/View;J)V",
                                                item->instance().object(),
                                                reinterpret_cast<jlong>(item));
        return adapter->m_holders.last().object();
    }
    return 0;
}

void QNativeAndroidRecyclerAdapter::onBindViewHolder(JNIEnv *env, jobject object, jlong instance, jobject holder, jint position)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QNativeAndroidRecyclerAdapter *adapter = reinterpret_cast<QNativeAndroidRecyclerAdapter *>(instance);
    if (adapter) {
        jlong vi = QAndroidJniObject(holder).callMethod<jlong>("getInstance");
        QNativeAndroidView *item = reinterpret_cast<QNativeAndroidView *>(vi);
        if (item)
            QMetaObject::invokeMethod(adapter, "setItemPosition", Qt::BlockingQueuedConnection, Q_ARG(QNativeAndroidView *, item), Q_ARG(int, position));
    }
}

QNativeAndroidView *QNativeAndroidRecyclerAdapter::createItem()
{
    QNativeAndroidView *item = nullptr;
    if (m_delegate) {
        QQmlContext *creationContext = m_delegate->creationContext();
        QQmlContext *context = new QQmlContext(creationContext ? creationContext : qmlContext(this));
        QObject *object = m_delegate->beginCreate(context);
        if (object) {
            context->setParent(object);
            item = qobject_cast<QNativeAndroidView *>(object);
            if (!item)
                delete object;
        } else {
            delete context;
        }
    } else {
        item = new QNativeAndroidView;
    }
    if (item) {
        item->setContext(context());
        item->setParentView(qobject_cast<QNativeAndroidView *>(parent())); // TODO
        setItemPosition(item, -1);
    }
    if (m_delegate)
        m_delegate->completeCreate();
    return item;
}

void QNativeAndroidRecyclerAdapter::setItemPosition(QNativeAndroidView *item, int position)
{
    QQmlContext *context = qmlContext(item);
    if (context)
        context = context->parentContext();
    if (context)
        context->setContextProperty("position", position);
}

QT_END_NAMESPACE
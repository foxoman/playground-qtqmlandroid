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

#include "qnativeandroidimageview_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

QNativeAndroidImageView::QNativeAndroidImageView(QNativeAndroidContext *context) :
    QNativeAndroidView(context), m_resource(0)
{
}

QUrl QNativeAndroidImageView::imageURI() const
{
    return m_uri;
}

void QNativeAndroidImageView::setImageURI(const QUrl &uri)
{
    if (m_uri != uri) {
        m_uri = uri;
        if (isValid()) {
            QAndroidJniObject v = instance();
            QAndroidJniObject u = getUri();
            QtQmlAndroid::callFunction([=]() {
                v.callMethod<void>("setImageURI", "(Landroid/net/Uri;)V", u.object());
            });
        }
        emit imageURIChanged();
    }
}

int QNativeAndroidImageView::imageResource() const
{
    return m_resource;
}

void QNativeAndroidImageView::setImageResource(int resource)
{
    if (m_resource != resource) {
        m_resource = resource;
        QtQmlAndroid::callIntMethod(instance(), "setImageResource", resource);
        emit imageResourceChanged();
    }
}

int QNativeAndroidImageView::imageTintColor() const
{
    if (m_tint.isNull())
        return 0; // TODO
    return m_tint;
}

void QNativeAndroidImageView::setImageTintColor(int color)
{
    if (m_tint.isNull() || m_tint != color) {
        m_tint = color;
        if (isValid()) {
            QAndroidJniObject view = instance();
            QtQmlAndroid::callFunction([=]() {
                QAndroidJniObject tint = QAndroidJniObject::callStaticObjectMethod("android/content/res/ColorStateList",
                                                                                   "valueOf",
                                                                                   "(I)Landroid/content/res/ColorStateList;",
                                                                                   color);
                view.callMethod<void>("setImageTintList", "(Landroid/content/res/ColorStateList;)v", tint.object());
            });
        }
        emit imageTintColorChanged();
    }
}

QAndroidJniObject QNativeAndroidImageView::onCreate()
{
    return QAndroidJniObject("android/widget/ImageView",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QNativeAndroidImageView::onInflate(QAndroidJniObject &instance)
{
    QNativeAndroidView::onInflate(instance);

    if (m_uri.isValid())
        instance.callMethod<void>("setImageURI", "(Landroid/net/Uri;)V", getUri().object());
    if (m_resource > 0)
        instance.callMethod<void>("setImageResource", "(I)V", m_resource);
    if (!m_tint.isNull()) {
        QAndroidJniObject tint = QAndroidJniObject::callStaticObjectMethod("android/content/res/ColorStateList",
                                                                           "valueOf",
                                                                           "(I)Landroid/content/res/ColorStateList;",
                                                                           m_tint);
        instance.callMethod<void>("setImageTintList", "(Landroid/content/res/ColorStateList;)v", tint.object());
    }
}

QAndroidJniObject QNativeAndroidImageView::getUri() const
{
    QAndroidJniObject str = QAndroidJniObject::fromString(m_uri.toString());
    return QAndroidJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", str.object());
}

QT_END_NAMESPACE

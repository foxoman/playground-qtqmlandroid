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

#ifndef QNATIVEANDROIDLAYOUTPARAMS_P_H
#define QNATIVEANDROIDLAYOUTPARAMS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQmlAndroid/private/qnativeandroidobject_p.h>
#include <QtQmlAndroid/private/qnativeandroidoptional_p.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QNativeAndroidView;

class Q_QMLANDROID_EXPORT QNativeAndroidLayoutParams : public QNativeAndroidObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_ENUMS(Size)

public:
    explicit QNativeAndroidLayoutParams(QNativeAndroidView *view);

    static QNativeAndroidLayoutParams *qmlAttachedProperties(QObject *object);

    enum Size {
        FILL_PARENT = -1,
        MATCH_PARENT = -1,
        WRAP_CONTENT = -2
    };

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

public Q_SLOTS:
    void invalidate();

Q_SIGNALS:
    void widthChanged();
    void heightChanged();

protected:
    QAndroidJniObject onCreate() override;
    void onInflate(QAndroidJniObject &instance) override;

    bool event(QEvent *event) override;

private:
    bool m_dirty;
    QNativeAndroidView *m_view;
    QNativeAndroidOptional<int> m_width;
    QNativeAndroidOptional<int> m_height;
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QNativeAndroidLayoutParams, QML_HAS_ATTACHED_PROPERTIES)

#endif // QNATIVEANDROIDLAYOUTPARAMS_P_H
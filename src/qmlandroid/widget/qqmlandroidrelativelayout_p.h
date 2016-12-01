#ifndef QQMLANDROIDRELATIVELAYOUT_P_H
#define QQMLANDROIDRELATIVELAYOUT_P_H

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

#include "qqmlandroidviewgroup_p.h"
#include "qqmlandroidrelativelayoutparams_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidRelativeLayout : public QQmlAndroidViewGroup
{
    Q_OBJECT

public:
    explicit QQmlAndroidRelativeLayout(QQmlAndroidView *parent = 0);

    static QQmlAndroidRelativeLayoutParams *qmlAttachedProperties(QObject *object);

    enum Verb {
        LEFT_OF                  = 0,
        RIGHT_OF                 = 1,
        ABOVE                    = 2,
        BELOW                    = 3,
        ALIGN_BASELINE           = 4,
        ALIGN_LEFT               = 5,
        ALIGN_TOP                = 6,
        ALIGN_RIGHT              = 7,
        ALIGN_BOTTOM             = 8,
        ALIGN_PARENT_LEFT        = 9,
        ALIGN_PARENT_TOP         = 10,
        ALIGN_PARENT_RIGHT       = 11,
        ALIGN_PARENT_BOTTOM      = 12,
        CENTER_IN_PARENT         = 13,
        CENTER_HORIZONTAL        = 14,
        CENTER_VERTICAL          = 15,
        START_OF                 = 16,
        END_OF                   = 17,
        ALIGN_START              = 18,
        ALIGN_END                = 19,
        ALIGN_PARENT_START       = 20,
        ALIGN_PARENT_END         = 21
    };

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QQmlAndroidRelativeLayout, QML_HAS_ATTACHED_PROPERTIES)

#endif // QQMLANDROIDRELATIVELAYOUT_P_H

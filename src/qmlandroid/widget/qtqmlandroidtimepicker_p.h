#ifndef QTQMLANDROIDTIMEPICKER_P_H
#define QTQMLANDROIDTIMEPICKER_P_H

#include "qtqmlandroidframelayout_p.h"

QT_BEGIN_NAMESPACE

class QtQmlAndroidTimePicker : public QtQmlAndroidFrameLayout
{
    Q_OBJECT

public:
    explicit QtQmlAndroidTimePicker(QtQmlAndroidView *parent = 0);

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QTQMLANDROIDTIMEPICKER_P_H
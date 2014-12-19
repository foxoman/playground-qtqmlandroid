#ifndef QTQMLANDROIDSEARCHVIEW_P_H
#define QTQMLANDROIDSEARCHVIEW_P_H

#include "qtqmlandroidlinearlayout_p.h"

QT_BEGIN_NAMESPACE

class QtQmlAndroidSearchView : public QtQmlAndroidLinearLayout
{
    Q_OBJECT

public:
    explicit QtQmlAndroidSearchView(QtQmlAndroidView *parent = 0);

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QTQMLANDROIDSEARCHVIEW_P_H
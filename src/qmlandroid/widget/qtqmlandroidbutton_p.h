#ifndef QTQMLANDROIDBUTTON_P_H
#define QTQMLANDROIDBUTTON_P_H

#include "qtqmlandroidtextview_p.h"

QT_BEGIN_NAMESPACE

class QtQmlAndroidButton : public QtQmlAndroidTextView
{
    Q_OBJECT

public:
    explicit QtQmlAndroidButton(QtQmlAndroidView *parent = 0);

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QTQMLANDROIDBUTTON_P_H
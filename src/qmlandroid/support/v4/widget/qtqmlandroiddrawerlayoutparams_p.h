#ifndef QTQMLANDROIDDRAWERLAYOUTPARAMS_P_H
#define QTQMLANDROIDDRAWERLAYOUTPARAMS_P_H

#include "qtqmlandroidmarginlayoutparams_p.h"

QT_BEGIN_NAMESPACE

class QtQmlAndroidDrawerLayoutParams : public QtQmlAndroidMarginLayoutParams
{
    Q_OBJECT
    Q_PROPERTY(int gravity READ gravity WRITE setGravity NOTIFY gravityChanged) // TODO Gravity

public:
    explicit QtQmlAndroidDrawerLayoutParams(QtQmlAndroidView *view);

    int gravity() const;
    void setGravity(int gravity);

Q_SIGNALS:
    void gravityChanged();

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;

private:
    int m_gravity;
};

QT_END_NAMESPACE

#endif // QTQMLANDROIDDRAWERLAYOUTPARAMS_P_H
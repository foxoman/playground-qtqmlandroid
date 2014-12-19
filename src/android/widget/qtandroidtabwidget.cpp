#include "qtandroidtabwidget_p.h"

QT_BEGIN_NAMESPACE

QtAndroidTabWidget::QtAndroidTabWidget(QtAndroidView *parent) :
    QtAndroidLinearLayout(parent)
{
    setIdentifier(16908307); // TODO: android.R.id.tabs
}

QAndroidJniObject QtAndroidTabWidget::onCreate()
{
    return QAndroidJniObject("android/widget/TabWidget",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QtAndroidTabWidget::onInflate(QAndroidJniObject &instance)
{
    QtAndroidLinearLayout::onInflate(instance);
}

QT_END_NAMESPACE
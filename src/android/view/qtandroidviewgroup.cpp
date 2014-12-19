#include "qtandroidviewgroup_p.h"
#include "qtandroidlayoutparams_p.h"
#include "qtandroidfunctions_p.h"
#include "qtandroidcontext_p.h"

QT_BEGIN_NAMESPACE

QtAndroidViewGroup::QtAndroidViewGroup(QtAndroidView *parent) :
    QtAndroidView(parent)
{
}

QtAndroidLayoutParams *QtAndroidViewGroup::qmlAttachedProperties(QObject *object)
{
    QtAndroidView *view = qobject_cast<QtAndroidView*>(object);
    if (view)
        return new QtAndroidLayoutParams(view);
    return 0;
}

QAndroidJniObject QtAndroidViewGroup::onCreate()
{
    return QAndroidJniObject("android/view/ViewGroup",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QtAndroidViewGroup::onInflate(QAndroidJniObject &instance)
{
    QtAndroidView::onInflate(instance);

    foreach (QtAndroidView *child, childViews())
        instance.callMethod<void>("addView", "(Landroid/view/View;)V", child->instance().object());
}

void QtAndroidViewGroup::viewChange(ViewChange change, const ViewChangeData &data)
{
    QAndroidJniObject group = instance();
    switch (change) {
    case ViewChildAddedChange: // data.view
        if (group.isValid()) {
//            QtAndroid::callFunction([=]() {
//                QAndroidJniObject child = data.view->onCreate();
//                data.view->onInflate(child);
//                data.view->setInstance(child);
//                group.callMethod<void>("addView", "(Landroid/view/View;)V", child.object());
//            });
        }
        break;
    case ViewChildRemovedChange: // data.view
        if (group.isValid()) {
//            QAndroidJniObject child = data.view->instance();
//            QtAndroid::callFunction([=]() {
//                group.callMethod<void>("removeView", "(Landroid/view/View;)V", child.object());
//            });
//            data.view->setInstance(QAndroidJniObject());
        }
        break;
    default:
        break;
    }
}

QT_END_NAMESPACE
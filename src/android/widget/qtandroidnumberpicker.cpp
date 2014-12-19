#include "qtandroidnumberpicker_p.h"
#include "qtandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

QtAndroidNumberPicker::QtAndroidNumberPicker(QtAndroidView *parent) :
    QtAndroidLinearLayout(parent), m_value(0)
{
}

int QtAndroidNumberPicker::value() const
{
    return m_value;
}

void QtAndroidNumberPicker::setValue(int value)
{
    if (updateValue(value))
        QtAndroid::callIntMethod(instance(), "setValue", value);
}

bool QtAndroidNumberPicker::updateValue(int value)
{
    if (m_value != value) {
        m_value = value;
        emit valueChanged();
        return true;
    }
    return false;
}

QAndroidJniObject QtAndroidNumberPicker::onCreate()
{
    return QAndroidJniObject("android/widget/NumberPicker",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QtAndroidNumberPicker::onInflate(QAndroidJniObject &instance)
{
    QtAndroidLinearLayout::onInflate(instance);

    m_listener = QAndroidJniObject("qt/android/widget/QtNumberPickerListener",
                                   "(Landroid/widget/NumberPicker;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        onRegisterNativeMethods(m_listener.object());
        nativeMethodsRegistered = true;
    }

    instance.callMethod<void>("setValue", "(I)V", m_value);
}

void QtAndroidNumberPicker::onRegisterNativeMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onValueChange", "(JI)V", reinterpret_cast<void *>(onValueChange)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

void QtAndroidNumberPicker::onValueChange(JNIEnv *env, jobject object, jlong instance, jint value)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QtAndroidNumberPicker *picker = reinterpret_cast<QtAndroidNumberPicker *>(instance);
    if (picker)
        QMetaObject::invokeMethod(picker, "updateValue", Qt::QueuedConnection, Q_ARG(int, value));
}

QT_END_NAMESPACE
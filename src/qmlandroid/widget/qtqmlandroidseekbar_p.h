#ifndef QTQMLANDROIDSEEKBAR_P_H
#define QTQMLANDROIDSEEKBAR_P_H

#include "qtqmlandroidabsseekbar_p.h"

QT_BEGIN_NAMESPACE

class QtQmlAndroidSeekBar : public QtQmlAndroidAbsSeekBar
{
    Q_OBJECT

public:
    explicit QtQmlAndroidSeekBar(QtQmlAndroidView *parent = 0);

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;

    static void onRegisterNativeMethods(jobject listener);
    static void onProgressChanged(JNIEnv *env, jobject object, jlong instance, jint progress, jboolean fromUser);

private:
    QAndroidJniObject m_listener;
};

QT_END_NAMESPACE

#endif // QTQMLANDROIDSEEKBAR_P_H
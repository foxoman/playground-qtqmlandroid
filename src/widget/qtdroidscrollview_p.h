#ifndef QTDROIDSCROLLVIEW_P_H
#define QTDROIDSCROLLVIEW_P_H

#include "qtdroidframelayout_p.h"

QT_BEGIN_NAMESPACE

class QtDroidScrollView : public QtDroidFrameLayout
{
    Q_OBJECT
    Q_PROPERTY(int scrollX READ scrollX WRITE setScrollX NOTIFY scrollXChanged)
    Q_PROPERTY(int scrollY READ scrollY WRITE setScrollY NOTIFY scrollYChanged)

public:
    explicit QtDroidScrollView(QtDroidView *parent = 0);

    int scrollX() const;
    void setScrollX(int x);

    int scrollY() const;
    void setScrollY(int y);

Q_SIGNALS:
    void scrollXChanged();
    void scrollYChanged();

protected:
    QAndroidJniObject construct() Q_DECL_OVERRIDE;
    void inflate() Q_DECL_OVERRIDE;

    static void registerNativeMethods(jobject listener);
    static void onScrollChanged(JNIEnv *env, jobject object, jlong instance, jint left, jint top);

private Q_SLOTS:
    bool updateScrollX(int x);
    bool updateScrollY(int y);

private:
    QtDroidOptional<int> m_scrollX;
    QtDroidOptional<int> m_scrollY;
};

QT_END_NAMESPACE

#endif // QTDROIDSCROLLVIEW_P_H

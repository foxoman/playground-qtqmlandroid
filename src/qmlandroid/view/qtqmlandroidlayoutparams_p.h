#ifndef QTQMLANDROIDLAYOUTPARAMS_P_H
#define QTQMLANDROIDLAYOUTPARAMS_P_H

#include "qtqmlandroidobject_p.h"
#include "qtqmlandroidoptional_p.h"
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QtQmlAndroidView;

class QtQmlAndroidLayoutParams : public QtQmlAndroidObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_ENUMS(Size)

public:
    explicit QtQmlAndroidLayoutParams(QtQmlAndroidView *view);

    static QtQmlAndroidLayoutParams *qmlAttachedProperties(QObject *object);

    enum Size {
        FILL_PARENT = -1,
        MATCH_PARENT = -1,
        WRAP_CONTENT = -2
    };

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

public Q_SLOTS:
    void invalidate();

Q_SIGNALS:
    void widthChanged();
    void heightChanged();

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;

    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_dirty;
    QtQmlAndroidView *m_view;
    QtQmlAndroidOptional<int> m_width;
    QtQmlAndroidOptional<int> m_height;
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QtQmlAndroidLayoutParams, QML_HAS_ATTACHED_PROPERTIES)

#endif // QTQMLANDROIDLAYOUTPARAMS_P_H
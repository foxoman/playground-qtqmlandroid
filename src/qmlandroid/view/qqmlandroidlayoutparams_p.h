#ifndef QQMLANDROIDLAYOUTPARAMS_P_H
#define QQMLANDROIDLAYOUTPARAMS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQmlAndroid/private/qqmlandroidobject_p.h>
#include <QtQmlAndroid/private/qqmlandroidoptional_p.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QQmlAndroidView;

class QQmlAndroidLayoutParams : public QQmlAndroidObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_ENUMS(Size)

public:
    explicit QQmlAndroidLayoutParams(QQmlAndroidView *view);

    static QQmlAndroidLayoutParams *qmlAttachedProperties(QObject *object);

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
    QQmlAndroidView *m_view;
    QQmlAndroidOptional<int> m_width;
    QQmlAndroidOptional<int> m_height;
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QQmlAndroidLayoutParams, QML_HAS_ATTACHED_PROPERTIES)

#endif // QQMLANDROIDLAYOUTPARAMS_P_H

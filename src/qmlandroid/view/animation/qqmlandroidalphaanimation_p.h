#ifndef QQMLANDROIDALPHAANIMATION_P_H
#define QQMLANDROIDALPHAANIMATION_P_H

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

#include "qqmlandroidanimation_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidAlphaAnimation : public QQmlAndroidAnimation
{
    Q_OBJECT
    Q_PROPERTY(qreal fromAlpha READ fromAlpha WRITE setFromAlpha NOTIFY fromAlphaChanged)
    Q_PROPERTY(qreal toAlpha READ toAlpha WRITE setToAlpha NOTIFY toAlphaChanged)

public:
    explicit QQmlAndroidAlphaAnimation(QObject *parent = 0);

    qreal fromAlpha() const;
    void setFromAlpha(qreal alpha);

    qreal toAlpha() const;
    void setToAlpha(qreal alpha);

Q_SIGNALS:
    void fromAlphaChanged();
    void toAlphaChanged();

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;

private:
    qreal m_fromAlpha;
    qreal m_toAlpha;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDALPHAANIMATION_P_H

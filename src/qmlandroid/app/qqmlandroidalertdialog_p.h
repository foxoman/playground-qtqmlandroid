#ifndef QQMLANDROIDALERTDIALOG_P_H
#define QQMLANDROIDALERTDIALOG_P_H

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

#include "qqmlandroiddialog_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidAlertDialog : public QQmlAndroidDialog
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)

public:
    explicit QQmlAndroidAlertDialog(QObject *parent = 0);

    QString title() const;
    void setTitle(const QString &title);

    QString message() const;
    void setMessage(const QString &message);

Q_SIGNALS:
    void titleChanged();
    void messageChanged();

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject& instance) Q_DECL_OVERRIDE;

private:
    QString m_title;
    QString m_message;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDALERTDIALOG_P_H

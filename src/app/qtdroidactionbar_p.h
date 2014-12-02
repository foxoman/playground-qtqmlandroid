#ifndef QTDROIDACTIONBAR_P_H
#define QTDROIDACTIONBAR_P_H

#include "qtdroidobject_p.h"

QT_BEGIN_NAMESPACE

class QtDroidActivity;

class QtDroidActionBar : public QtDroidObject
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle NOTIFY subtitleChanged)

public:
    explicit QtDroidActionBar(QObject *parent = 0);

    bool isVisible() const;
    void setVisible(bool visible);

    QString title() const;
    void setTitle(const QString &title);

    QString subtitle() const;
    void setSubtitle(const QString &subtitle);

    QtDroidActivity *activity() const;
    void setActivity(QtDroidActivity *activity);

Q_SIGNALS:
    void visibleChanged();
    void titleChanged();
    void subtitleChanged();

private:
    bool m_visible;
    QString m_title;
    QString m_subtitle;
    QtDroidActivity *m_activity;
};

QT_END_NAMESPACE

#endif // QTDROIDACTIONBAR_P_H

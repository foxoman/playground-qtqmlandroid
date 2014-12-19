#include "qtandroidpathinterpolator_p.h"

QT_BEGIN_NAMESPACE

QtAndroidPathInterpolator::QtAndroidPathInterpolator(QObject *parent) :
    QtAndroidInterpolator(parent)
{
}

qreal QtAndroidPathInterpolator::controlX() const
{
    if (m_controlX.isNull())
        return 0.0;
    return m_controlX.value();
}

void QtAndroidPathInterpolator::setControlX(qreal x)
{
    if (m_controlX.isNull() || m_controlX.value() != x) {
        m_controlX = x;
        emit controlXChanged();
    }
}

qreal QtAndroidPathInterpolator::controlY() const
{
    if (m_controlY.isNull())
        return 0.0;
    return m_controlY.value();
}

void QtAndroidPathInterpolator::setControlY(qreal y)
{
    if (m_controlY.isNull() || m_controlY.value() != y) {
        m_controlY = y;
        emit controlYChanged();
    }
}

qreal QtAndroidPathInterpolator::controlX2() const
{
    if (m_controlX2.isNull())
        return 0.0;
    return m_controlX2.value();
}

void QtAndroidPathInterpolator::setControlX2(qreal x)
{
    if (m_controlX2.isNull() || m_controlX2.value() != x) {
        m_controlX2 = x;
        emit controlX2Changed();
    }
}

qreal QtAndroidPathInterpolator::controlY2() const
{
    if (m_controlY2.isNull())
        return 0.0;
    return m_controlY2.value();
}

void QtAndroidPathInterpolator::setControlY2(qreal y)
{
    if (m_controlY2.isNull() || m_controlY2.value() != y) {
        m_controlY2 = y;
        emit controlY2Changed();
    }
}

QAndroidJniObject QtAndroidPathInterpolator::onCreate()
{
    if (!m_controlX.isNull() && !m_controlY.isNull() && !m_controlX2.isNull() && !m_controlY2.isNull())
        return QAndroidJniObject("android/view/animation/PathInterpolator",
                                 "(FFFF)V",
                                 m_controlX.value(),
                                 m_controlY.value(),
                                 m_controlX2.value(),
                                 m_controlY2.value());

    if (!m_controlX.isNull() && !m_controlY.isNull())
        return QAndroidJniObject("android/view/animation/PathInterpolator",
                                 "(FF)V",
                                 m_controlX.value(),
                                 m_controlY.value());

    return QAndroidJniObject();
}

QT_END_NAMESPACE
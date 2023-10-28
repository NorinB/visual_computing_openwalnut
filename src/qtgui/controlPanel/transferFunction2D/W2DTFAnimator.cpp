//---------------------------------------------------------------------------
//
// Project: OpenWalnut ( http://www.openwalnut.org )
//
// Copyright 2009 OpenWalnut Community, BSV@Uni-Leipzig and CNCF@MPI-CBS
// For more information see http://www.openwalnut.org/copying
//
// This file is part of OpenWalnut.
//
// OpenWalnut is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpenWalnut is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OpenWalnut. If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------------------------


#include <vector>
#include <algorithm>

#include "QPropertyAnimation"
#include "QParallelAnimationGroup"
#include "QAnimationGroup"
#include <QTimer>
#include "QVariantAnimation"

#include "W2DTFAnimator.h"
#include "core/common/WLogger.h"


W2DTFAnimator::W2DTFAnimator()
{
    m_sequential = false;
    m_updateRate = 0;
    m_updateTimer = new QTimer();
    m_subscriptionChanged = false;
    m_singleShotTimer = new QTimer();
    m_singleShotTimer->setSingleShot( true );
    m_paused = false;
}

W2DTFAnimator::~W2DTFAnimator()
{
}

void W2DTFAnimator::playAnimationsParallel()
{
    if( m_parallelGroup.state() == QAbstractAnimation::Running )
    {
        m_parallelGroup.stop();
        m_updateTimer->disconnect();
        m_updateTimer->stop();
    }

    m_parallelGroup.setLoopCount( -1 );
    if(  m_paused && ( !m_subscriptionChanged )  )
    {
        m_paused = false;
        m_parallelGroup.resume();
        m_updateTimer->start( m_updateRate );
    }
    else
    {
        m_parallelGroup.clear();
        m_subscriptionChanged = false;
        for( size_t i = 0; i < m_subscribedWidgets.size(); i++ )
        {
            std::vector<QPropertyAnimation*> animations = addAnimations( m_subscribedWidgets[i] );
            for( size_t i = 0; i < animations.size(); i++ )
            {
                m_parallelGroup.addAnimation( animations[i] );
            }
        }
        m_parallelGroup.start();
        m_updateTimer->start( m_updateRate );
    }
}

void W2DTFAnimator::stopAnimations()
{
    m_paused = false;
    m_parallelGroup.stop();
    m_parallelGroup.clear();
    m_updateTimer->disconnect();
    m_updateTimer->stop();
    m_singleShotTimer->start();
}

void W2DTFAnimator::pauseAnimations()
{
    m_parallelGroup.pause();
    m_paused = true;
    m_updateTimer->stop();
    m_singleShotTimer->start();
}

std::vector<QPropertyAnimation*> W2DTFAnimator::addAnimations( WTransferFunction2DShapeWidget* widget )
{
    std::vector<QPropertyAnimation*> animations;
    switch( widget->getAnimationData().getType() )
    {
        case S_TOPDOWN:
        {
            WTransferFunction2DControlPoint* top = NULL;
            if( widget->getControlPoints().size() == 3 )
            {
                top = getSortedPointAtRank( widget, 2, Y_ASCENDING );
            }
            else
            {
                top = getSortedPointAtRank( widget, 3, Y_ASCENDING );
            }
            animations.push_back( createAnimation( widget, top ) );
            break;
        }
        case S_BOTTOMUP:
        {
            WTransferFunction2DControlPoint* bottom = NULL;
            bottom = getSortedPointAtRank( widget, 0, Y_ASCENDING );
            animations.push_back( createAnimation( widget, bottom ) );
            break;
        }
        case S_MAX_Y:
        {
            WTransferFunction2DControlPoint* top = NULL;
            if( widget->getControlPoints().size() == 3 )
            {
                top = getSortedPointAtRank( widget, 2, Y_ASCENDING );
            }
            else
            {
                top = getSortedPointAtRank( widget, 3, Y_ASCENDING );
            }
            animations.push_back( createAnimation( widget, top ) );
            break;
        }
        case S_MIN_Y:
        {
            WTransferFunction2DControlPoint* bottom = NULL;
            bottom = getSortedPointAtRank( widget, 0, Y_ASCENDING );
            animations.push_back( createAnimation( widget, bottom ) );
            break;
        }
        case S_LEFT_TO_RIGHT:
        {
            WTransferFunction2DControlPoint* left = NULL;
            left = getSortedPointAtRank( widget, 0, X_ASCENDING );
            animations.push_back( createAnimation( widget, left ) );
            break;
        }
        case S_RIGHT_TO_LEFT:
        {
            WTransferFunction2DControlPoint* right = NULL;
            if( widget->getControlPoints().size() == 3 )
            {
                right = getSortedPointAtRank( widget, 2, X_ASCENDING );
            }
            else
            {
                right = getSortedPointAtRank( widget, 3, X_ASCENDING );
            }
            animations.push_back( createAnimation( widget, right ) );
            break;
        }
        case S_MAX_X:
        {
            WTransferFunction2DControlPoint* right = NULL;
            if( widget->getControlPoints().size() == 3 )
            {
                right = getSortedPointAtRank( widget, 2, X_ASCENDING );
            }
            else
            {
                right = getSortedPointAtRank( widget, 3, X_ASCENDING );
            }
            animations.push_back( createAnimation( widget, right ) );
            break;
        }
        case S_MIN_X:
        {
            WTransferFunction2DControlPoint* left = NULL;
            left = getSortedPointAtRank( widget, 0, X_ASCENDING );
            animations.push_back( createAnimation( widget, left ) );
            break;
        }
        case NO_ANIM:
            break;
        default:
            break;
    }
    return animations;
}

QPropertyAnimation* W2DTFAnimator::createAnimation( WTransferFunction2DShapeWidget* widget, WTransferFunction2DControlPoint* target )
{
    QPropertyAnimation* animation = new QPropertyAnimation( target , "pos", widget );
    animation->setDuration( calculateDuration( widget, target ) );
    animation->setKeyValues( getKeyValues( widget, target ) );
    m_parallelGroup.connect( m_updateTimer, &QTimer::timeout, target, &WTransferFunction2DControlPoint::controlPointMoved );
    m_parallelGroup.connect( m_singleShotTimer, &QTimer::timeout, target, &WTransferFunction2DControlPoint::controlPointMoved );

    return animation;
}

QVariantAnimation::KeyValues W2DTFAnimator::getKeyValues( WTransferFunction2DShapeWidget* widget,
                                                          WTransferFunction2DControlPoint* target )
{
    QVariantAnimation::KeyValues keyValues;
    switch( widget->getAnimationData().getType() )
    {
        case S_TOPDOWN:
            keyValues.append( QVariantAnimation::KeyValue( 0, QPointF( target->pos() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 0.5,
                                QPointF( target->pos().x(), getSortedPointAtRank( widget, 0, Y_ASCENDING )->y() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 1, QPointF( target->pos() ) ) );

            return keyValues;
            break;
        case S_BOTTOMUP:
            keyValues.append( QVariantAnimation::KeyValue( 0, QPointF( target->pos() ) ) );

            if( widget->getControlPoints().size() == 3 ) // if widget has three points --> triangle
            {
                keyValues.append( QVariantAnimation::KeyValue( 0.5,
                                    QPointF( target->pos().x(), getSortedPointAtRank( widget, 2, Y_ASCENDING )->y() ) ) );
            }
            else    // widget has 4 points --> e.g. box, quadrangle, ellipsis
            {
                keyValues.append( QVariantAnimation::KeyValue( 0.5,
                                    QPointF( target->pos().x(), getSortedPointAtRank( widget, 3, Y_ASCENDING )->y() ) ) );
            }
            keyValues.append( QVariantAnimation::KeyValue( 1, QPointF( target->pos() ) ) );

            return keyValues;
            break;
        case S_MAX_Y:

            keyValues.append( QVariantAnimation::KeyValue( 0, QPointF( target->pos() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 0.5, QPointF( target->pos().x(),
                                                            target->mapToParent( target->mapFromScene( QPointF( 0, 300 ) ) ).y() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 1, QPointF( target->pos() ) ) );

            return keyValues;
            break;
        case S_MIN_Y:
            keyValues.append( QVariantAnimation::KeyValue( 0, QPointF( target->pos() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 0.5, QPointF( target->pos().x(),
                                                            target->mapToParent( target->mapFromScene( QPointF( 0, 0 ) ) ).y() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 1, QPointF( target->pos() ) ) );

            return keyValues;
            break;
        case S_LEFT_TO_RIGHT:
            keyValues.append( QVariantAnimation::KeyValue( 0, QPointF( target->pos() ) ) );

            if( widget->getControlPoints().size() == 3 ) // if widget has three points --> triangle
            {
                keyValues.append( QVariantAnimation::KeyValue( 0.5,
                                    QPointF( getSortedPointAtRank( widget, 2, X_ASCENDING )->x(), target->pos().y() ) ) );
            }
            else    // widget has 4 points --> e.g. box, quadrangle, ellipsis
            {
                keyValues.append( QVariantAnimation::KeyValue( 0.5,
                                    QPointF( getSortedPointAtRank( widget, 3, X_ASCENDING )->x(), target->pos().y() ) ) );
            }
            keyValues.append( QVariantAnimation::KeyValue( 1, QPointF( target->pos() ) ) );

            return keyValues;
            break;
        case S_RIGHT_TO_LEFT:
            keyValues.append( QVariantAnimation::KeyValue( 0, QPointF( target->pos() ) ) );
                keyValues.append( QVariantAnimation::KeyValue( 0.5,
                                    QPointF( getSortedPointAtRank( widget, 0, X_ASCENDING )->x(), target->pos().y() ) ) );
            keyValues.append( QVariantAnimation::KeyValue( 1, QPointF( target->pos() ) ) );
            return keyValues;
            break;
        case S_MIN_X:
            keyValues.append( QVariantAnimation::KeyValue( 0, QPointF( target->pos() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 0.5, QPointF( target->mapToParent( target->mapFromScene( QPointF( 0, 0 ) ) ).x(),
                                                        target->pos().y() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 1, QPointF( target->pos() ) ) );

            return keyValues;
            break;
        case S_MAX_X:
            keyValues.append( QVariantAnimation::KeyValue( 0, QPointF( target->pos() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 0.5, QPointF( target->mapToParent( target->mapFromScene( QPointF( 300, 0 ) ) ).x(),
                                                        target->pos().y() ) ) );

            keyValues.append( QVariantAnimation::KeyValue( 1, QPointF( target->pos() ) ) );

            return keyValues;
            break;
        case NO_ANIM:
            return keyValues;
            break;
        default:
            return keyValues;
            break;
    }
}

WTransferFunction2DControlPoint* W2DTFAnimator::getSortedPointAtRank( WTransferFunction2DShapeWidget* widget, int rank, PointSortPolicy policy )
{
    std::vector<WTransferFunction2DControlPoint*> points = widget->getControlPoints();

    switch( policy )
    {
        case Y_ASCENDING:
            std::sort( points.begin(), points.end(), []( WTransferFunction2DControlPoint* a, WTransferFunction2DControlPoint* b )
            {
                return a->pos().y() < b->pos().y();
            } );
            break;
        case X_ASCENDING:
            std::sort( points.begin(), points.end(), []( WTransferFunction2DControlPoint* a, WTransferFunction2DControlPoint* b )
            {
                return a->pos().x() < b->pos().x();
            } );
            break;
        case NO_POLICY:
            break;
        default:
            break;
    }
    return points[rank];
}

bool W2DTFAnimator::isPaused()
{
    return m_paused;
}

int W2DTFAnimator::calculateDuration( WTransferFunction2DShapeWidget* widget, [[maybe_unused]] WTransferFunction2DControlPoint* target )
{
    int duration = 5000;
    //TODO(T.Neeb): Find a way to increase speed but have all animations have same duration
    switch( widget->getAnimationData().getType() )
    {
        case S_TOPDOWN:
            duration = 5000 / widget->getAnimSpeed();
            break;
        case S_BOTTOMUP:
            duration = 5000 / widget->getAnimSpeed();
            break;
        case S_MAX_Y:
            duration = 5000 / widget->getAnimSpeed();
            break;
        case S_MIN_Y:
            duration = 5000 / widget->getAnimSpeed();
            break;
        case S_LEFT_TO_RIGHT:
            duration = 5000 / widget->getAnimSpeed();
            break;
        case S_RIGHT_TO_LEFT:
            duration = 5000 / widget->getAnimSpeed();
            break;
        case S_MAX_X:
            duration = 5000 / widget->getAnimSpeed();
            break;
        case S_MIN_X:
            duration = 5000 / widget->getAnimSpeed();
            break;
        case NO_ANIM:
            break;
        default:
            break;
    }
    return duration;
}

void W2DTFAnimator::setUpdateRate( int newRate )
{
    m_updateRate = newRate;
}

void W2DTFAnimator::subscribeWidget( WTransferFunction2DShapeWidget* widget )
{
    auto it = std::find( m_subscribedWidgets.begin(), m_subscribedWidgets.end(), widget );
    if( it != m_subscribedWidgets.end() )
    {
        m_subscribedWidgets.erase( it );
    }
    m_subscribedWidgets.push_back( widget );
    m_subscriptionChanged = true;
}

void W2DTFAnimator::unsubscribeWidget( WTransferFunction2DShapeWidget* widget )
{
    for( size_t i = 0; i < m_subscribedWidgets.size(); i++ )
    {
        if( m_subscribedWidgets[i] == widget )
        {
            m_subscribedWidgets.erase( m_subscribedWidgets.begin() + i );
        }
    }
    m_subscriptionChanged = true;
}

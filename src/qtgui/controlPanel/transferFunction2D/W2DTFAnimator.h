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

#ifndef W2DTFANIMATOR_H
#define W2DTFANIMATOR_H

#include <vector>

#include "QPropertyAnimation"
#include "QParallelAnimationGroup"
#include "QAnimationGroup"
#include <QTimer>
#include "QVariantAnimation"

#include "WTransferFunction2DWidgetAnimationData.h"
#include "WTransferFunction2DShapeWidget.h"
#include "WTransferFunction2DControlPoint.h"

class WTransferFunction2DShapeWidget;

/**
 * A subscription-based class that manages and processes animations for the classification widgets of the 2DTF
 * 
 */
class W2DTFAnimator
{
public:
/**
 * @brief Construct a new W2DTFAnimator object
 * 
 */
W2DTFAnimator();

/**
 * @brief Destroy the W2DTFAnimator object
 * 
 */
~W2DTFAnimator();

/**
 * @brief Puts all animations into a parallelAnimationGroup an plays them
 * 
 */
void playAnimationsParallel();

/**
 * @brief Stops all playing animations
 * 
 */
void stopAnimations();


/**
 * @brief Pauses all playing animations
 * 
 */
void pauseAnimations();

/**
 * @brief Subscribes a widget with its currently selected animation to the animator
 * 
 * @param widget 
 */
void subscribeWidget( WTransferFunction2DShapeWidget *widget );

/**
 * @brief unsubscribes the widget from the animator
 * 
 * @param widget 
 */
void unsubscribeWidget( WTransferFunction2DShapeWidget *widget );

/**
 * @brief Set the UpdateRate of the animator
 * 
 * @param newRate 
 */
void setUpdateRate( int newRate );

/**
 * @brief returns the m_paused state
 * 
 * @return true 
 * @return false 
 */
bool isPaused();

private:
/**
 * @brief Returns an animation to be added to an animationGroup
 * 
 * @param widget 
 * @return QPropertyAnimation 
 */
std::vector<QPropertyAnimation*> addAnimations( WTransferFunction2DShapeWidget* widget );

/**
 * @brief Calculates the KeyValuePoints as QPoints so the KeyValues for each animation are indivudally adapted 
 * 
 * @param widget 
 * @param target 
 * @return QVariantAnimation::KeyValues 
 */
QVariantAnimation::KeyValues getKeyValues( WTransferFunction2DShapeWidget* widget, WTransferFunction2DControlPoint* target );

/**
 * @brief calculates the duration based on speed setting
 * 
 * @param widget 
 * @param target
 * @return int 
 */
int calculateDuration( WTransferFunction2DShapeWidget* widget, [[maybe_unused]] WTransferFunction2DControlPoint* target );

/**
 * @brief Returns a WTransferControlPoint of the given widget at a certain rank after the point-vector of the widget got sorted restricted by the PointSortPolicy
 * 
 * @param widget 
 * @param rank 
 * @param policy 
 * @return WTransferFunction2DControlPoint* 
 */
WTransferFunction2DControlPoint* getSortedPointAtRank( WTransferFunction2DShapeWidget* widget, int rank, PointSortPolicy policy );

/**
 * @brief Creates a QPropertyAnimation for the given parameters and returns a pointer to it
 * 
 * @param widget 
 * @param target
 * @return QPropertyAnimation* 
 */
QPropertyAnimation* createAnimation( WTransferFunction2DShapeWidget* widget, WTransferFunction2DControlPoint* target );

/**
 * @brief List of pointers to subscribed widgets
 */
std::vector<WTransferFunction2DShapeWidget*> m_subscribedWidgets;

/**
 * @brief the animation group that is used when all animations are played in parallel
 */
QParallelAnimationGroup m_parallelGroup;

/**
 * @brief Parent of the animator
 */
QObject m_parent;

/**
 * @brief timer that is updated at specific rates to call widget update functions
 */
QTimer* m_updateTimer;

/**
 * @brief a timer that is used to update the transferFunction once the animation has finished so the state of the widgets is as expected
 */
QTimer* m_singleShotTimer;

/**
 * @brief state that defines whether the animations are played in parallel or sequential
 */
bool m_sequential;

/**
 * @brief state that changes to true when a subscription or unsubscription took place
 * 
 */
bool m_subscriptionChanged;

/**
 * @brief state that changes to true when the animationGroup is paused
 * 
 */
bool m_paused;

/**
 * @brief the interval in miliseconds in which the transferfunction-state gets updated and delivered to the DVR-Module
 * values lower than 200 may result in non-consistent behaviour of the animation.
 * a value of 0 will update the tf everytime the computational load of each animation-step has been computed
 */
int m_updateRate;
};

#endif  // W2DTFANIMATOR_H

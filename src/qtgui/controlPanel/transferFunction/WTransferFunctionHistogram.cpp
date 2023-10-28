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

#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

#include "WTransferFunctionHistogram.h"
#include "WTransferFunctionWidget.h"

#include "QPainter"
#include "QStyleOption"
#include "QGraphicsSceneMouseEvent"


WTransferFunctionHistogram::WTransferFunctionHistogram( WTransferFunctionWidget * /*parent*/ ) : BaseClass()
{
    setOpacity( 0.4 );
    setZValue( 2 );
}

WTransferFunctionHistogram::~WTransferFunctionHistogram()
{
}

QRectF WTransferFunctionHistogram::boundingRect() const
{
    return scene()->sceneRect();
}

void WTransferFunctionHistogram::paint( QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget* )
{
    const int steps = m_data.size();
    if( steps > 0 )
    {
        double maxval = *std::max_element( m_data.begin(), m_data.end() );
        if( maxval > 0.0 )
        {
            QRadialGradient gradient( 0.0, 0.0, 10 );
            painter->setBrush( gradient );
            gradient.setColorAt( 0, Qt::white );
            gradient.setColorAt( 1, Qt::black );

            painter->setBrush( gradient );

            // polygon for logarithmic mapping ( background )
            {
                QPolygon histogram;
                QRectF bb( this->scene()->sceneRect() );
                histogram << QPoint( bb.right(), bb.bottom() );
                histogram << QPoint( bb.left(), bb.bottom() );

                for( int i = 0; i < steps; ++i )
                {
                    // logarithmic mapping of histogram to values
                    // the added 0.001 is to avoid numerical problems but should work for most data sets
                    // when changing this value, keep in mind that the value has to work for a wide range of
                    // numbers ( i.e. maxval close to 0 and maxval close to infty )
                    histogram << QPoint( bb.left()+ ( double )bb.width()*( double )i/( double )steps,
                              bb.bottom() - ( double )bb.height() * std::log( m_data[ i ]+1 )/std::log( maxval+1+0.001 ) );
                }
                painter->drawPolygon( histogram );
            }
            // The paper "Multi-Dimensional Transfer Functions for Interactive Volume Rendering"
            // by Joe Kniss, Gordon Kindlmann and Charles Hansen
            // brought the idea of overlaying the logarithmic plot with a non-logarithmic plot
            // which may help to understand the data a bit better. Maybe this should be a config option,
            // but for now it is there for whoever likes to see it.
            //
            // polygon for non-logarithmic mapping
            {
                QPolygon histogram;
                QRectF bb( this->scene()->sceneRect() );
                histogram << QPoint( bb.right(), bb.bottom() );
                histogram << QPoint( bb.left(), bb.bottom() );

                for( int i = 0; i < steps; ++i )
                {
                    // linear mapping of histogram to values
                    histogram << QPoint( bb.left()+ ( double )bb.width()*( double )i/( double )steps,
                              bb.bottom() - ( double )bb.height() * m_data[ i ]/maxval );
                }
                painter->drawPolygon( histogram );
            }
        }
    }
}

const std::vector< double >& WTransferFunctionHistogram::getData() const
{
    return m_data;
}

std::vector< double >& WTransferFunctionHistogram::getData()
{
    return m_data;
}


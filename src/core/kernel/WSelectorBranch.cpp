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

#include <list>
#include <memory>
#include <vector>

#include "WSelectorBranch.h"

WSelectorBranch::WSelectorBranch( std::shared_ptr< const WDataSetFibers > fibers, std::shared_ptr<WRMBranch> branch ) :
    m_fibers( fibers ),
    m_size( fibers->size() ),
    m_dirty( true ),
    m_branch( branch )
{
    m_bitField = std::shared_ptr< std::vector<bool> >( new std::vector<bool>( m_size, false ) );

    m_changeSignal =
        std::shared_ptr< boost::function< void() > >( new boost::function< void() >( boost::bind( &WSelectorBranch::setDirty, this ) ) );
    m_branch->addChangeNotifier( m_changeSignal );

    m_changeRoiSignal =
        std::shared_ptr< boost::function< void() > >( new boost::function< void() >( boost::bind( &WSelectorBranch::setDirty, this ) ) );
}

WSelectorBranch::~WSelectorBranch()
{
    m_branch->removeChangeNotifier( m_changeSignal );

    // We need the following because not all ROIs are removed per slot below
    for( std::list< std::shared_ptr< WSelectorRoi > >::iterator roiIter = m_rois.begin(); roiIter != m_rois.end(); ++roiIter )
    {
        ( *roiIter )->getRoi()->removeROIChangeNotifier( m_changeRoiSignal );
    }
}

void WSelectorBranch::addRoi( std::shared_ptr< WSelectorRoi > roi )
{
    m_rois.push_back( roi );
    roi->getRoi()->addROIChangeNotifier( m_changeRoiSignal );
}

std::list< std::shared_ptr< WSelectorRoi > > WSelectorBranch::getROIs()
{
    return m_rois;
}

void WSelectorBranch::setDirty()
{
    m_dirty = true;
}

void WSelectorBranch::removeRoi( osg::ref_ptr< WROI > roi )
{
    for( std::list< std::shared_ptr< WSelectorRoi > >::iterator iter = m_rois.begin(); iter != m_rois.end(); ++iter )
    {
        if( ( *iter )->getRoi() == roi )
        {
            ( *iter )->getRoi()->removeROIChangeNotifier( m_changeRoiSignal );
            m_rois.erase( iter );
            break;
        }
    }
}

void WSelectorBranch::recalculate()
{
    bool atLeastOneActive = false;

    for( std::list< std::shared_ptr< WSelectorRoi > >::iterator iter = m_rois.begin(); iter != m_rois.end(); ++iter )
    {
        if( ( *iter )->getRoi()->active() )
        {
            atLeastOneActive = true;
        }
    }

    if( atLeastOneActive )
    {
        m_workerBitfield = std::shared_ptr< std::vector< bool > >( new std::vector< bool >( m_size, true ) );

        for( std::list< std::shared_ptr< WSelectorRoi > >::iterator iter = m_rois.begin(); iter != m_rois.end(); ++iter )
        {
            if( ( *iter )->getRoi()->active() )
            {
                std::shared_ptr< std::vector<bool> > bf = ( *iter )->getBitField();
                bool isnot = ( *iter )->getRoi()->isNot();
                if( !isnot )
                {
                    for( size_t i = 0 ; i < m_size ; ++i )
                    {
                        ( *m_workerBitfield )[i] = ( *m_workerBitfield )[i] & ( *bf )[i];
                    }
                }
                else
                {
                    for( size_t i = 0 ; i < m_size ; ++i )
                    {
                        ( *m_workerBitfield )[i] = ( *m_workerBitfield )[i] & !( *bf )[i];
                    }
                }
            }
        }

        if( m_branch->isNot() )
        {
           for( size_t i = 0 ; i < m_size ; ++i )
            {
                ( *m_workerBitfield )[i] = !( *m_workerBitfield )[i];
            }
        }
    }
    else
    {
        m_workerBitfield = std::shared_ptr< std::vector< bool > >( new std::vector< bool >( m_size, false ) );
    }

    m_bitField = m_workerBitfield;
}

WColor WSelectorBranch::getBranchColor() const
{
    return m_branch->colorProperty()->toPropColor()->get( true );
}

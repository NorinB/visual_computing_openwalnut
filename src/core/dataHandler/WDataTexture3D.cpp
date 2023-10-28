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

#include <memory>
#include <string>

#include "../graphicsEngine/WGETextureUtils.h"
#include "WDataTexture3D.h"
#include "WValueSet.h"

WDataTexture3D::WDataTexture3D( std::shared_ptr< WValueSetBase > valueSet, std::shared_ptr< WGridRegular3D > grid ):
    WGETexture3D( static_cast< float >( valueSet->getMaximumValue() - valueSet->getMinimumValue() ),
                  static_cast< float >( valueSet->getMinimumValue() ) ),
    m_valueSet( valueSet ),
    m_boundingBox( grid->getVoxelBoundingBox() )
{
    // initialize members
    setTextureSize( grid->getNbCoordsX(), grid->getNbCoordsY(), grid->getNbCoordsZ() );

    // data textures do not repeat or something
    setWrap( osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE  );
    setWrap( osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE  );
    setWrap( osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE  );

    thresholdLower()->setMin( valueSet->getMinimumValue() );
    thresholdLower()->setMax( valueSet->getMaximumValue() );
    thresholdLower()->set( valueSet->getMinimumValue() );
    thresholdUpper()->setMin( valueSet->getMinimumValue() );
    thresholdUpper()->setMax( valueSet->getMaximumValue() );
    thresholdUpper()->set( valueSet->getMaximumValue() );

    window()->set( make_interval( valueSet->getMinimumValue(),
                                  valueSet->getMaximumValue() ) );

    // Scale according to bbox. This scaling is NOT included in the grid's transform, so we need to add it here
    WMatrix4d scale = WMatrix4d::zero();
    scale( 0, 0 ) = 1.0 / grid->getNbCoordsX();
    scale( 1, 1 ) = 1.0 / grid->getNbCoordsY();
    scale( 2, 2 ) = 1.0 / grid->getNbCoordsZ();
    scale( 3, 3 ) = 1.0;

    // Move to voxel center. This scaling is NOT included in the grid's transform, so we need to add it here
    WMatrix4d offset = WMatrix4d::identity();
    offset( 3, 0 ) = 0.5 / grid->getNbCoordsX();
    offset( 3, 1 ) = 0.5 / grid->getNbCoordsY();
    offset( 3, 2 ) = 0.5 / grid->getNbCoordsZ();

    WMatrix4d const m = grid->getTransform(); // implicit cast
    Eigen::Matrix4d em = m;

    transformation()->set( WMatrix4d( em.inverse() ) * scale * offset );

    // set the size
    WGETexture3D::initTextureSize( this, grid->getNbCoordsX(), grid->getNbCoordsY(), grid->getNbCoordsZ() );
}

WDataTexture3D::~WDataTexture3D()
{
    // cleanup
}

void WDataTexture3D::create()
{
    osg::ref_ptr< osg::Image > ima;

    if( m_valueSet->getDataType() == W_DT_UINT8 )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_UINT8";
        std::shared_ptr< WValueSet< uint8_t > > vs = std::dynamic_pointer_cast< WValueSet< uint8_t > >( m_valueSet );
        uint8_t* source = const_cast< uint8_t* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_INT8 )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_INT8";
        std::shared_ptr< WValueSet< int8_t > > vs = std::dynamic_pointer_cast< WValueSet< int8_t > >( m_valueSet );
        int8_t* source = const_cast< int8_t* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_INT16 )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_INT16";
        std::shared_ptr< WValueSet< int16_t > > vs = std::dynamic_pointer_cast< WValueSet< int16_t > >( m_valueSet );
        int16_t* source = const_cast< int16_t* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_UINT16 )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_UINT16";
        std::shared_ptr< WValueSet< uint16_t > > vs = std::dynamic_pointer_cast< WValueSet< uint16_t > >( m_valueSet );
        uint16_t* source = const_cast< uint16_t* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_UINT32 )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_UINT32";
        std::shared_ptr< WValueSet< uint32_t > > vs = std::dynamic_pointer_cast< WValueSet< uint32_t > >( m_valueSet );
        uint32_t* source = const_cast< uint32_t* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_INT64 )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_INT64";
        std::shared_ptr< WValueSet< int64_t > > vs = std::dynamic_pointer_cast< WValueSet< int64_t > >( m_valueSet );
        int64_t* source = const_cast< int64_t* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_UINT64 )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_UINT64";
        std::shared_ptr< WValueSet< uint64_t > > vs = std::dynamic_pointer_cast< WValueSet< uint64_t > >( m_valueSet );
        uint64_t* source = const_cast< uint64_t* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_SIGNED_INT )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_SIGNED_INT";
        std::shared_ptr< WValueSet< int32_t > > vs = std::dynamic_pointer_cast< WValueSet< int32_t > >( m_valueSet );
        int* source = const_cast< int* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_FLOAT )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_FLOAT";
        std::shared_ptr< WValueSet< float > > vs = std::dynamic_pointer_cast< WValueSet< float > >( m_valueSet );
        float* source = const_cast< float* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_DOUBLE )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_DOUBLE";
        std::shared_ptr< WValueSet< double > > vs = std::dynamic_pointer_cast< WValueSet< double > >( m_valueSet );
        double* source = const_cast< double* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else if( m_valueSet->getDataType() == W_DT_FLOAT128 )
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type W_DT_FLOAT128";
        std::shared_ptr< WValueSet< long double > > vs = std::dynamic_pointer_cast< WValueSet< long double > >( m_valueSet );
        long double* source = const_cast< long double* > ( vs->rawData() );
        ima = createTexture( source, m_valueSet->dimension() );
    }
    else
    {
        wlog::debug( "WDataTexture3D" ) << "Creating Texture of type " << m_valueSet->getDataType();
        wlog::error( "WDataTexture3D" ) << "Conversion of this data type to texture not supported yet.";
    }

    // remove our link to the value set here. It can be free'd now if no one else uses it anymore
    m_valueSet.reset();

    setImage( ima );
    dirtyTextureObject();
}

WBoundingBox WDataTexture3D::getBoundingBox() const
{
    return m_boundingBox;
}

void wge::bindTexture( osg::ref_ptr< osg::Node > node, osg::ref_ptr< WDataTexture3D > texture, size_t unit, std::string prefix )
{
    wge::bindTexture( node, osg::ref_ptr< WGETexture3D >( texture ), unit, prefix );
}


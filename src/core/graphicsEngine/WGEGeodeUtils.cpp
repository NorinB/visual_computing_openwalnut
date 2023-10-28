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

#include <map>
#include <string>
#include <vector>

#include <osg/Array>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LightModel>
#include <osg/LineWidth>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Vec3>

#include "../common/math/WMath.h"
#include "../common/WPathHelper.h"
#include "../common/WStringUtils.h"

#include "shaders/WGEShader.h"
#include "WGEGeodeUtils.h"
#include "WGEGeometryUtils.h"
#include "WGEGroupNode.h"
#include "WGESubdividedPlane.h"
#include "WGEUtils.h"
#include "widgets/labeling/WGELabel.h"

osg::ref_ptr< osg::Geode > wge::generateBoundingBoxGeode( const WBoundingBox& bb, const WColor& color )
{
    const WBoundingBox::vec_type& pos1 = bb.getMin();
    const WBoundingBox::vec_type& pos2 = bb.getMax();

    WAssert( pos1[0] <= pos2[0] && pos1[1] <= pos2[1] && pos1[2] <= pos2[2], "pos1 does not seem to be the frontLowerLeft corner of the BB!" );
    using osg::ref_ptr;
    ref_ptr< osg::Vec3Array > vertices = ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
    ref_ptr< osg::Vec4Array > colors = ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
    ref_ptr< osg::Geometry > geometry = ref_ptr< osg::Geometry >( new osg::Geometry );

    vertices->push_back( osg::Vec3( pos1[0], pos1[1], pos1[2] ) );
    vertices->push_back( osg::Vec3( pos2[0], pos1[1], pos1[2] ) );
    vertices->push_back( osg::Vec3( pos2[0], pos2[1], pos1[2] ) );
    vertices->push_back( osg::Vec3( pos1[0], pos2[1], pos1[2] ) );
    vertices->push_back( osg::Vec3( pos1[0], pos1[1], pos1[2] ) );
    vertices->push_back( osg::Vec3( pos1[0], pos1[1], pos2[2] ) );
    vertices->push_back( osg::Vec3( pos2[0], pos1[1], pos2[2] ) );
    vertices->push_back( osg::Vec3( pos2[0], pos2[1], pos2[2] ) );
    vertices->push_back( osg::Vec3( pos1[0], pos2[1], pos2[2] ) );
    vertices->push_back( osg::Vec3( pos1[0], pos1[1], pos2[2] ) );

    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINE_STRIP, 0, vertices->size() ) );

    vertices->push_back( osg::Vec3( pos1[0], pos2[1], pos1[2] ) );
    vertices->push_back( osg::Vec3( pos1[0], pos2[1], pos2[2] ) );
    vertices->push_back( osg::Vec3( pos2[0], pos2[1], pos1[2] ) );
    vertices->push_back( osg::Vec3( pos2[0], pos2[1], pos2[2] ) );
    vertices->push_back( osg::Vec3( pos2[0], pos1[1], pos1[2] ) );
    vertices->push_back( osg::Vec3( pos2[0], pos1[1], pos2[2] ) );

    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINES, vertices->size() - 6, 6 ) );

    geometry->setVertexArray( vertices );
    colors->push_back( color );
    geometry->setColorArray( colors );
    geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
    osg::ref_ptr< osg::Geode > geode = osg::ref_ptr< osg::Geode >( new osg::Geode );
    geode->setName( "Bounding Box Geode" );
    geode->addDrawable( geometry );

    // disable light for this geode as lines can't be lit properly
    osg::StateSet* state = geode->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );

    return geode;
}

void wge::createCube( osg::ref_ptr< osg::Geometry > geometry, const WPosition& position, const WPosition& size, const WColor& color )
{
    // the geometry might be empty: ensure we have arrays properly set. If they cannot be casted, they get overwritten later. Users own fault if
    // he does not read the doc
    osg::ref_ptr< osg::Vec3Array > vertices = dynamic_cast< osg::Vec3Array* >( geometry->getVertexArray() );
    osg::ref_ptr< osg::Vec3Array > tex = dynamic_cast< osg::Vec3Array* >( geometry->getTexCoordArray( 0 ) );
    osg::ref_ptr< osg::Vec3Array > normals = dynamic_cast< osg::Vec3Array* >( geometry->getNormalArray() );
    osg::ref_ptr< osg::Vec4Array > colors = dynamic_cast< osg::Vec4Array* >( geometry->getColorArray() );

    // get some mem if not already done
    if( !vertices )
    {
        vertices = osg::ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
    }
    if( !tex )
    {
        tex = osg::ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
    }
    if( !normals )
    {
        normals = osg::ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
    }
    if( !colors )
    {
        colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
    }

    size_t first = vertices->getNumElements();

    // NOTE: as the OSG 3.2 does not allow binding normals/colors and other arrays on a per-primitive basis, we bind the normals per vertex
    // This means we add four normals per face

    // front face
    vertices->push_back( position + WPosition( 0.0,      0.0,      0.0 ) );
    vertices->push_back( position + WPosition( size.x(), 0.0,      0.0 ) );
    vertices->push_back( position + WPosition( size.x(), size.y(), 0.0 ) );
    vertices->push_back( position + WPosition( 0.0,      size.y(), 0.0 ) );
    tex->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );
    tex->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
    tex->push_back( osg::Vec3( 1.0, 1.0, 0.0 ) );
    tex->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
    normals->push_back( osg::Vec3( 0.0, 0.0, -1.0 ) );
    normals->push_back( osg::Vec3( 0.0, 0.0, -1.0 ) );
    normals->push_back( osg::Vec3( 0.0, 0.0, -1.0 ) );
    normals->push_back( osg::Vec3( 0.0, 0.0, -1.0 ) );

    // back face
    vertices->push_back( position + WPosition( 0.0,      0.0,      size.z() ) );
    vertices->push_back( position + WPosition( size.x(), 0.0,      size.z() ) );
    vertices->push_back( position + WPosition( size.x(), size.y(), size.z() ) );
    vertices->push_back( position + WPosition( 0.0,      size.y(), size.z() ) );
    tex->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );
    tex->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) );
    tex->push_back( osg::Vec3( 1.0, 1.0, 1.0 ) );
    tex->push_back( osg::Vec3( 0.0, 1.0, 1.0 ) );
    normals->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );
    normals->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );
    normals->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );
    normals->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );

    // left
    vertices->push_back( position + WPosition( 0.0, 0.0,      0.0 ) );
    vertices->push_back( position + WPosition( 0.0, size.y(), 0.0 ) );
    vertices->push_back( position + WPosition( 0.0, size.y(), size.z() ) );
    vertices->push_back( position + WPosition( 0.0, 0.0,      size.z() ) );
    tex->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );
    tex->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
    tex->push_back( osg::Vec3( 0.0, 1.0, 1.0 ) );
    tex->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );
    normals->push_back( osg::Vec3( -1.0, 0.0, 0.0 ) );
    normals->push_back( osg::Vec3( -1.0, 0.0, 0.0 ) );
    normals->push_back( osg::Vec3( -1.0, 0.0, 0.0 ) );
    normals->push_back( osg::Vec3( -1.0, 0.0, 0.0 ) );

    // right
    vertices->push_back( position + WPosition( size.x(), 0.0,      0.0 ) );
    vertices->push_back( position + WPosition( size.x(), size.y(), 0.0 ) );
    vertices->push_back( position + WPosition( size.x(), size.y(), size.z() ) );
    vertices->push_back( position + WPosition( size.x(), 0.0,      size.z() ) );
    tex->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
    tex->push_back( osg::Vec3( 1.0, 1.0, 0.0 ) );
    tex->push_back( osg::Vec3( 1.0, 1.0, 1.0 ) );
    tex->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) );
    normals->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
    normals->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
    normals->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
    normals->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );

    // bottom
    vertices->push_back( position + WPosition( 0.0,      0.0, 0.0 ) );
    vertices->push_back( position + WPosition( size.x(), 0.0, 0.0 ) );
    vertices->push_back( position + WPosition( size.x(), 0.0, size.z() ) );
    vertices->push_back( position + WPosition( 0.0,      0.0, size.z() ) );
    tex->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );
    tex->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
    tex->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) );
    tex->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );
    normals->push_back( osg::Vec3( 0.0, -1.0, 0.0 ) );
    normals->push_back( osg::Vec3( 0.0, -1.0, 0.0 ) );
    normals->push_back( osg::Vec3( 0.0, -1.0, 0.0 ) );
    normals->push_back( osg::Vec3( 0.0, -1.0, 0.0 ) );

    // top
    vertices->push_back( position + WPosition( 0.0,      size.y(), 0.0 ) );
    vertices->push_back( position + WPosition( size.x(), size.y(), 0.0 ) );
    vertices->push_back( position + WPosition( size.x(), size.y(), size.z() ) );
    vertices->push_back( position + WPosition( 0.0,      size.y(), size.z() ) );
    tex->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
    tex->push_back( osg::Vec3( 1.0, 1.0, 0.0 ) );
    tex->push_back( osg::Vec3( 1.0, 1.0, 1.0 ) );
    tex->push_back( osg::Vec3( 0.0, 1.0, 1.0 ) );
    normals->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
    normals->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
    normals->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
    normals->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );

    // set it up and set arrays
    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, first, 6 * 4 ) ); // 6 faces, 4 vertices per face
    geometry->setVertexArray( vertices );

    // set 3D texture coordinates here.
    geometry->setTexCoordArray( 0, tex );

    // set normals
    geometry->setNormalArray( normals );
    geometry->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );

    // finally, the colors
    colors->push_back( color );
    geometry->setColorArray( colors );
    geometry->setColorBinding( osg::Geometry::BIND_PER_PRIMITIVE_SET );
}

osg::ref_ptr< osg::Geometry > wge::createCube( const WPosition& position, const WPosition& size, const WColor& color )
{
    // create the unit cube manually as the ShapeDrawable and osg::Box does not provide 3D texture coordinates
    osg::ref_ptr< osg::Geometry > cube = new osg::Geometry();
    createCube( cube, position, size, color );
    return cube;
}

osg::ref_ptr< osg::Geometry > wge::createUnitCube( const WColor& color )
{
    // create the unit cube manually as the ShapeDrawable and osg::Box does not provide 3D texture coordinates
    return createCube( WPosition( 0.0, 0.0, 0.0 ), WPosition( 1.0, 1.0, 1.0 ), color );
}

osg::ref_ptr< osg::Geometry > wge::createUnitCubeAsLines( const WColor& color, bool asLines )
{
    // create the unit cube manually as the ShapeDrawable and osg::Box does not provide 3D texture coordinates
    osg::ref_ptr< osg::Geometry > cube = new osg::Geometry();
    osg::ref_ptr< osg::Vec3Array > vertices = osg::ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
    osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );

    if( !asLines )
    {
        vertices->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 1.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 1.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 1.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );

        cube->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINE_STRIP, 0, vertices->size() ) );

        vertices->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 1.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 1.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 1.0, 1.0 ) );

        cube->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINES, vertices->size() - 6, 6 ) );
    }
    else
    {
        vertices->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );

        vertices->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 1.0, 0.0 ) );

        vertices->push_back( osg::Vec3( 1.0, 1.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );

        vertices->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );

        vertices->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );

        vertices->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) );

        vertices->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 1.0, 1.0 ) );

        vertices->push_back( osg::Vec3( 1.0, 1.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 1.0, 1.0 ) );

        vertices->push_back( osg::Vec3( 0.0, 1.0, 1.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 0.0, 1.0 ) );

        vertices->push_back( osg::Vec3( 0.0, 1.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 0.0, 1.0, 1.0 ) );

        vertices->push_back( osg::Vec3( 1.0, 0.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 0.0, 1.0 ) );

        vertices->push_back( osg::Vec3( 1.0, 1.0, 0.0 ) );
        vertices->push_back( osg::Vec3( 1.0, 1.0, 1.0 ) );

        cube->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINES, 0, vertices->size() ) );
    }

    // set it up and set arrays
    cube->setVertexArray( vertices );

    // set 3D texture coordinates here.
    cube->setTexCoordArray( 0, vertices );

    // finally, the colors
    colors->push_back( color );
    cube->setColorArray( colors );
    cube->setColorBinding( osg::Geometry::BIND_OVERALL );

    return cube;
}

osg::ref_ptr< osg::Node > wge::generateSolidBoundingBoxNode( const WBoundingBox& bb, const WColor& color, bool threeDTexCoords )
{
    WAssert( bb.valid(), "Invalid bounding box!" );

    // create a uni cube
    osg::ref_ptr< osg::Geode > cube = new osg::Geode();
    cube->setName( "Solid Bounding Box" );
    if( threeDTexCoords )
    {
        cube->addDrawable( createUnitCube( color ) );
    }
    else
    {
        osg::ref_ptr< osg::ShapeDrawable > cubeDrawable = new osg::ShapeDrawable( new osg::Box( osg::Vec3( 0.5, 0.5, 0.5 ), 1.0 ) );
        cubeDrawable->setColor( color );
        cube->addDrawable( cubeDrawable );
    }

    // transform the cube to match the bbox
    osg::Matrixd transformM;
    osg::Matrixd scaleM;
    transformM.makeTranslate( bb.getMin() );
    scaleM.makeScale( bb.getMax() - bb.getMin() );

    // apply transformation to bbox
    osg::ref_ptr< osg::MatrixTransform > transform = new osg::MatrixTransform();
    transform->setMatrix( scaleM * transformM );
    transform->addChild( cube );

    // we do not need light
    osg::StateSet* state = cube->getOrCreateStateSet();
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );

    return transform;
}

osg::ref_ptr< osg::Geometry > wge::convertToOsgGeometry( WTriangleMesh::SPtr mesh,
                                                          const WColor& defaultColor,
                                                          bool includeNormals,
                                                          bool lighting,
                                                          bool useMeshColor )
{
    osg::ref_ptr< osg::Geometry> geometry( new osg::Geometry );
    geometry->setVertexArray( mesh->getVertexArray() );

    osg::DrawElementsUInt* surfaceElement;

    surfaceElement = new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, 0 );

    std::vector< size_t > tris = mesh->getTriangles();
    surfaceElement->reserve( tris.size() );

    for( unsigned int vertId = 0; vertId < tris.size(); ++vertId )
    {
        surfaceElement->push_back( tris[vertId] );
    }
    geometry->addPrimitiveSet( surfaceElement );

    // add the mesh colors
    if( mesh->getVertexColorArray() && useMeshColor )
    {
        geometry->setColorArray( mesh->getVertexColorArray() );
        geometry->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    }
    else
    {
        osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
        colors->push_back( defaultColor );
        geometry->setColorArray( colors );
        geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
    }

    // ------------------------------------------------
    // normals
    if( includeNormals )
    {
        geometry->setNormalArray( mesh->getVertexNormalArray() );
        geometry->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );

        if( lighting )
        {
            // if normals are specified, we also setup a default lighting.
            osg::StateSet* state = geometry->getOrCreateStateSet();
            osg::ref_ptr<osg::LightModel> lightModel = new osg::LightModel();
            lightModel->setTwoSided( true );
            state->setAttributeAndModes( lightModel.get(), osg::StateAttribute::ON );
            state->setMode( GL_BLEND, osg::StateAttribute::ON  );
            {
                osg::ref_ptr< osg::Material > material = new osg::Material();
                material->setDiffuse(   osg::Material::FRONT, osg::Vec4( 1.0, 1.0, 1.0, 1.0 ) );
                material->setSpecular(  osg::Material::FRONT, osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
                material->setAmbient(   osg::Material::FRONT, osg::Vec4( 0.1, 0.1, 0.1, 1.0 ) );
                material->setEmission(  osg::Material::FRONT, osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
                material->setShininess( osg::Material::FRONT, 25.0 );
                state->setAttribute( material );
            }
        }
    }

    // enable VBO
    geometry->setUseDisplayList( false );
    geometry->setUseVertexBufferObjects( true );

    return geometry;
}

osg::ref_ptr< osg::Geometry > wge::convertToOsgGeometryFlatShaded( WTriangleMesh::SPtr mesh,
                                                                    const WColor& defaultColor,
                                                                    bool includeNormals,
                                                                    bool lighting,
                                                                    bool useMeshColor )
{
    osg::DrawElementsUInt* surfaceElement;
    surfaceElement = new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES, 0 );
    std::vector< size_t > tris = mesh->getTriangles();

    osg::ref_ptr< osg::Geometry> geometry( new osg::Geometry );
    osg::ref_ptr< osg::Vec3Array > oldVertexArray( mesh->getVertexArray() );
    osg::ref_ptr< osg::Vec3Array > newVertexArray( new osg::Vec3Array );
    osg::ref_ptr< osg::Vec4Array > oldVertexColorArray( mesh->getVertexColorArray() );
    osg::ref_ptr< osg::Vec4Array > newVertexColorArray( new osg::Vec4Array );

    // Make separate vertices for all triangle corners
    for( size_t index = 0; index < tris.size(); ++index )
    {
        newVertexArray->push_back( (*oldVertexArray)[tris[index]] );
        surfaceElement->push_back( index );
        newVertexColorArray->push_back( (*oldVertexColorArray)[tris[index]] );
    }
    geometry->setVertexArray( newVertexArray );
    geometry->addPrimitiveSet( surfaceElement );

    // add the mesh colors
    if( mesh->getVertexColorArray() && useMeshColor )
    {
        geometry->setColorArray( newVertexColorArray );
        geometry->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    }
    else
    {
        osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
        colors->push_back( defaultColor );
        geometry->setColorArray( colors );
        geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
    }

    // ------------------------------------------------
    // normals
    if( includeNormals )
    {
        // Set all vertex normals to the normals of the corresponding
        // triangles causing uniform shading in a triangle
        osg::ref_ptr< osg::Vec3Array > oldTriNormals = mesh->getTriangleNormalArray( true );
        osg::ref_ptr< osg::Vec3Array > newVertNormals( new osg::Vec3Array );
        for( size_t index = 0; index < tris.size(); ++index )
        {
            newVertNormals->push_back( (*oldTriNormals)[index/3] );
        }
        geometry->setNormalArray( newVertNormals );
        geometry->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );

        if( lighting )
        {
            // if normals are specified, we also setup a default lighting.
            osg::StateSet* state = geometry->getOrCreateStateSet();
            osg::ref_ptr<osg::LightModel> lightModel = new osg::LightModel();
            lightModel->setTwoSided( true );
            state->setAttributeAndModes( lightModel.get(), osg::StateAttribute::ON );
            state->setMode( GL_BLEND, osg::StateAttribute::ON  );
            {
                osg::ref_ptr< osg::Material > material = new osg::Material();
                material->setDiffuse(   osg::Material::FRONT, osg::Vec4( 1.0, 1.0, 1.0, 1.0 ) );
                material->setSpecular(  osg::Material::FRONT, osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
                material->setAmbient(   osg::Material::FRONT, osg::Vec4( 0.1, 0.1, 0.1, 1.0 ) );
                material->setEmission(  osg::Material::FRONT, osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
                material->setShininess( osg::Material::FRONT, 25.0 );
                state->setAttribute( material );
            }
        }
    }

    // enable VBO
    geometry->setUseDisplayList( false );
    geometry->setUseVertexBufferObjects( true );

    return geometry;
}

osg::ref_ptr< osg::Geometry > wge::convertToOsgGeometry( WTriangleMesh::SPtr mesh,
                                                          const WColoredVertices& colorMap,
                                                          const WColor& defaultColor,
                                                          bool includeNormals, bool lighting )
{
    osg::ref_ptr< osg::Geometry >  geometry = convertToOsgGeometry( mesh, defaultColor, includeNormals, lighting, false );

    // ------------------------------------------------
    // colors
    osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
    for( size_t i = 0; i < mesh->vertSize(); ++i )
    {
        colors->push_back( defaultColor );
    }
    for( std::map< size_t, WColor >::const_iterator vc = colorMap.getData().begin(); vc != colorMap.getData().end(); ++vc )
    {
        // ATTENTION: the colormap might not be available and hence an old one, but the new mesh might have triggered the update
        if( vc->first < colors->size() )
        {
            colors->at( vc->first ) = vc->second;
        }
    }

    geometry->setColorArray( colors );
    geometry->setColorBinding( osg::Geometry::BIND_PER_VERTEX );

    return geometry;
}

osg::ref_ptr< osg::Geometry > wge::convertToOsgGeometryLines( WTriangleMesh::SPtr mesh,
                                                              const WColor& defaultColor,
                                                              bool useMeshColor )
{
    osg::ref_ptr< osg::Geometry > geometry( new osg::Geometry );
    geometry->setVertexArray( mesh->getVertexArray() );

    osg::DrawElementsUInt* meshElement;

    meshElement = new osg::DrawElementsUInt( osg::PrimitiveSet::LINES, 0 );

    std::vector< size_t > tris = mesh->getTriangles();
    meshElement->reserve( tris.size() * 3 );

    for( unsigned int triId = 0; triId < tris.size() / 3.; ++triId )
    {
        for( size_t edgeId = 0; edgeId < 3; ++edgeId )
        {
            meshElement->push_back( tris[triId*3 + edgeId] );
            meshElement->push_back( tris[triId*3 + ( edgeId + 1 ) % 3] );
        }
    }
    geometry->addPrimitiveSet( meshElement );

    // add the mesh colors
    if( mesh->getVertexColorArray() && useMeshColor )
    {
        geometry->setColorArray( mesh->getVertexColorArray() );
        geometry->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    }
    else
    {
        osg::ref_ptr< osg::Vec4Array > colors = osg::ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
        colors->push_back( defaultColor );
        geometry->setColorArray( colors );
        geometry->setColorBinding( osg::Geometry::BIND_OVERALL );
    }

    osg::StateSet* stateset = geometry->getOrCreateStateSet();
    stateset->setAttributeAndModes( new osg::LineWidth( 1 ), osg::StateAttribute::ON );
    stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    stateset->setMode( GL_BLEND, osg::StateAttribute::ON );

    return geometry;
}

osg::ref_ptr< osg::PositionAttitudeTransform > wge::addLabel( osg::Vec3 position, std::string text )
{
    osg::ref_ptr< osgText::Text > label = osg::ref_ptr< osgText::Text >( new osgText::Text() );
    osg::ref_ptr< osg::Geode > labelGeode = osg::ref_ptr< osg::Geode >( new osg::Geode() );

    labelGeode->addDrawable( label );

    // setup font
    label->setFont( WPathHelper::getAllFonts().Default.string() );
    label->setBackdropType( osgText::Text::OUTLINE );
    label->setCharacterSize( 6 );

    label->setText( text );
    label->setAxisAlignment( osgText::Text::SCREEN );
    label->setDrawMode( osgText::Text::TEXT );
    label->setAlignment( osgText::Text::CENTER_TOP );
    label->setPosition( osg::Vec3( 0.0, 0.0, 0.0 ) );
    label->setColor( osg::Vec4( 1.0f, 1.0f, 1.0f, 1.0f ) );

    osg::ref_ptr< osg::PositionAttitudeTransform > labelXform =
        osg::ref_ptr< osg::PositionAttitudeTransform >( new osg::PositionAttitudeTransform() );
    labelXform->setPosition( position );

    labelXform->addChild( labelGeode );

    return labelXform;
}

osg::ref_ptr< osg::PositionAttitudeTransform > wge::vector2label( osg::Vec3 position )
{
    std::string label = "(" + string_utils::toString( position[0] ) + "," +
    string_utils::toString( position[1] ) + "," + string_utils::toString( position[2] ) + ")";
    return ( addLabel( position, label ) );
}

osg::ref_ptr< osg::Geode > wge::genFinitePlane( double xSize, double ySize, const WPlane& p, const WColor& color, bool border )
{
    using osg::ref_ptr;
    ref_ptr< osg::Vec3Array > vertices = ref_ptr< osg::Vec3Array >( new osg::Vec3Array );
    ref_ptr< osg::Vec4Array > colors   = ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
    ref_ptr< osg::Geometry >  geometry = ref_ptr< osg::Geometry >( new osg::Geometry );

    colors->push_back( color );

    vertices->push_back( p.getPointInPlane(  xSize,  ySize ) );
    vertices->push_back( p.getPointInPlane( -xSize,  ySize ) );
    vertices->push_back( p.getPointInPlane( -xSize, -ySize ) );
    vertices->push_back( p.getPointInPlane(  xSize, -ySize ) );

    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );
    geometry->setVertexArray( vertices );
    geometry->setColorArray( colors );
    geometry->setColorBinding( osg::Geometry::BIND_OVERALL );

    osg::StateSet* stateset = new osg::StateSet;
    stateset->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    geometry->setStateSet( stateset );

    osg::ref_ptr< osg::Geode > geode = osg::ref_ptr< osg::Geode >( new osg::Geode );
    geode->setName( "Finite Plane Geode" );
    geode->addDrawable( geometry );

    if( border )
    {
        vertices->push_back( vertices->front() );
        ref_ptr< osg::Geometry >  borderGeom = ref_ptr< osg::Geometry >( new osg::Geometry );
        borderGeom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINE_STRIP, 0, 4 ) );
        borderGeom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::LINE_STRIP, 3, 2 ) );
        ref_ptr< osg::Vec4Array > colors   = ref_ptr< osg::Vec4Array >( new osg::Vec4Array );
        colors->push_back( inverseColor( color ) );
        borderGeom->setColorArray( colors );
        borderGeom->setColorBinding( osg::Geometry::BIND_OVERALL );
        borderGeom->setVertexArray( vertices );
        geode->addDrawable( borderGeom );
    }
    return geode;
}

osg::ref_ptr< osg::Geode > wge::genFinitePlane( osg::Vec3 const& base, osg::Vec3 const& a, osg::Vec3 const& b, const WColor& color )
{
    // the stuff needed by the OSG to create a geometry instance
    osg::ref_ptr< osg::Vec3Array > vertices = new osg::Vec3Array;
    osg::ref_ptr< osg::Vec3Array > texcoords0 = new osg::Vec3Array;
    osg::ref_ptr< osg::Vec3Array > normals = new osg::Vec3Array;
    osg::ref_ptr< osg::Vec4Array > colors = new osg::Vec4Array;

    osg::Vec3 aPlusB = a + b;

    vertices->push_back( base );
    vertices->push_back( base + a );
    vertices->push_back( base + aPlusB );
    vertices->push_back( base + b );

    osg::Vec3 aCrossB = a ^ b;
    aCrossB.normalize();
    osg::Vec3 aNorm = a;
    aNorm.normalize();
    osg::Vec3 bNorm = b;
    bNorm.normalize();

    normals->push_back( aCrossB );
    normals->push_back( aCrossB );
    normals->push_back( aCrossB );
    normals->push_back( aCrossB );
    colors->push_back( color );
    colors->push_back( color );
    colors->push_back( color );
    colors->push_back( color );
    texcoords0->push_back( osg::Vec3( 0.0, 0.0, 0.0 ) );
    texcoords0->push_back( aNorm );
    texcoords0->push_back( aNorm + bNorm );
    texcoords0->push_back( bNorm );

    // put it all together
    osg::ref_ptr< osg::Geometry > geometry = new osg::Geometry();
    geometry->setVertexArray( vertices );
    geometry->setTexCoordArray( 0, texcoords0 );
    geometry->setNormalArray( normals );
    geometry->setColorArray( colors );
    geometry->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

    osg::ref_ptr< osg::Geode > geode = new osg::Geode();
    geode->setName( "Finite Plane" );
    geode->addDrawable( geometry );
    return geode;
}

osg::ref_ptr< osg::Group > wge::creatCoordinateSystem(
    osg::Vec3 middle,
    double sizeX,
    double sizeY,
    double sizeZ
)
{
    osg::ref_ptr< WGEGroupNode >groupNode = new WGEGroupNode();
    osg::ref_ptr< WGEShader > shaderCoordinateSystem( new WGEShader( "WGECoordinateSystem" ) );

    osg::ref_ptr< osg::Geode > graphX( new osg::Geode );
    osg::ref_ptr< osg::Geode > graphY( new osg::Geode );
    osg::ref_ptr< osg::Geode > graphZ( new osg::Geode );

    osg::ref_ptr< osg::Geode > graphXCylinder( new osg::Geode );
    osg::ref_ptr< osg::Geode > graphYCylinder( new osg::Geode );
    osg::ref_ptr< osg::Geode > graphZCylinder( new osg::Geode );

    // X
    osg::ref_ptr< osg::ShapeDrawable > cylinderX = new osg::ShapeDrawable( new osg::Cylinder(
        middle, 1, sizeX + ( sizeX * 0.5 )
    ) );
    osg::ref_ptr< osg::ShapeDrawable > cylinderXEnd = new osg::ShapeDrawable( new osg::Cylinder(
        osg::Vec3( middle.x(), middle.y(), middle.z() - ( sizeX + ( sizeX * 0.5 ) ) / 2.0 ), 1.0, 1.0
    ) );
    osg::ref_ptr< osg::ShapeDrawable > coneX = new osg::ShapeDrawable( new osg::Cone(
        osg::Vec3( middle.x(), middle.y(), middle.z() + ( sizeX + ( sizeX * 0.5 ) ) / 2.0 ), 2.0, 5.0
    ) );
    cylinderXEnd->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    graphXCylinder->addDrawable( cylinderX );
    graphX->addDrawable( coneX );
    graphX->addDrawable( cylinderXEnd );

    osg::ref_ptr< osg::Material > matX = new osg::Material();
    matX->setDiffuse( osg::Material::FRONT, WColor( 1.0, 0.0, 0.0, 1.0 ) );
    cylinderX->getOrCreateStateSet()->setAttribute( matX, osg::StateAttribute::ON );
    coneX->getOrCreateStateSet()->setAttribute( matX, osg::StateAttribute::ON );

    // Y
    osg::ref_ptr< osg::ShapeDrawable > cylinderY = new osg::ShapeDrawable( new osg::Cylinder(
        middle, 1, sizeY + ( sizeY * 0.5 )
    ) );
    osg::ref_ptr< osg::ShapeDrawable > cylinderYEnd = new osg::ShapeDrawable( new osg::Cylinder(
        osg::Vec3( middle.x(), middle.y(), middle.z() - ( sizeY + ( sizeY * 0.5 ) ) / 2.0 ), 1.0, 1.0
    ) );
    osg::ref_ptr< osg::ShapeDrawable > coneY = new osg::ShapeDrawable( new osg::Cone(
        osg::Vec3( middle.x(), middle.y(), middle.z() + ( sizeY + ( sizeY * 0.5 ) ) / 2.0 ), 2.0, 5.0
    ) );
    cylinderYEnd->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

    graphYCylinder->addDrawable( cylinderY );
    graphY->addDrawable( coneY );
    graphY->addDrawable( cylinderYEnd );

    osg::ref_ptr< osg::Material > matY = new osg::Material();
    matY->setDiffuse( osg::Material::FRONT, WColor( 0.0, 1.0, 0.0, 1.0 ) );
    cylinderY->getOrCreateStateSet()->setAttribute( matY, osg::StateAttribute::ON );
    coneY->getOrCreateStateSet()->setAttribute( matY, osg::StateAttribute::ON );


    // Z
    osg::ref_ptr< osg::ShapeDrawable > cylinderZ = new osg::ShapeDrawable( new osg::Cylinder(
        middle, 1, sizeZ + ( sizeZ * 0.5 )
    ) );
    osg::ref_ptr< osg::ShapeDrawable > cylinderZEnd = new osg::ShapeDrawable( new osg::Cylinder(
        osg::Vec3( middle.x(), middle.y(), middle.z() - ( sizeZ + ( sizeZ * 0.5 ) ) / 2.0 ), 1.0, 1.0
    ) );
    osg::ref_ptr< osg::ShapeDrawable > coneZ = new osg::ShapeDrawable( new osg::Cone(
        osg::Vec3( middle.x(), middle.y(), middle.z() + ( sizeZ + ( sizeZ * 0.5 ) ) / 2.0 ), 2.0, 5.0
    ) );
    cylinderZEnd->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

    graphZCylinder->addDrawable( cylinderZ );
    graphZ->addDrawable( coneZ );
    graphZ->addDrawable( cylinderZEnd );

    osg::ref_ptr< osg::Material > matZ = new osg::Material();
    matZ->setDiffuse( osg::Material::FRONT, WColor( 0.0, 0.0, 1.0, 1.0 ) );
    cylinderZ->getOrCreateStateSet()->setAttribute( matZ, osg::StateAttribute::ON );
    coneZ->getOrCreateStateSet()->setAttribute( matZ, osg::StateAttribute::ON );

    shaderCoordinateSystem->apply( graphXCylinder );
    shaderCoordinateSystem->apply( graphYCylinder );
    shaderCoordinateSystem->apply( graphZCylinder );

    osg::ref_ptr< WGELabel > graphXLabel = new WGELabel();
    graphXLabel->setText( "X" );
    graphXLabel->setCharacterSize( 10 );
    graphXLabel->setPosition( osg::Vec3( middle.x(), middle.y(), middle.z() + ( sizeX + ( sizeX * 0.5 ) ) / 2.0 + 5.0 ) );
    graphXLabel->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    graphX->addDrawable( graphXLabel );

    osg::ref_ptr< WGELabel > graphYLabel = new WGELabel();
    graphYLabel->setText( "Y" );
    graphYLabel->setCharacterSize( 10 );
    graphYLabel->setPosition( osg::Vec3( middle.x(), middle.y(), middle.z() + ( sizeY + ( sizeY * 0.5 ) ) / 2.0 + 5.0 ) );
    graphYLabel->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    graphY->addDrawable( graphYLabel );

    osg::ref_ptr< WGELabel > graphZLabel = new WGELabel();
    graphZLabel->setText( "Z" );
    graphZLabel->setCharacterSize( 10 );
    graphZLabel->setPosition( osg::Vec3( middle.x(), middle.y(), middle.z() + ( sizeZ + ( sizeZ * 0.5 ) ) / 2.0 + 5.0 ) );
    graphZLabel->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    graphZ->addDrawable( graphZLabel );


    osg::ref_ptr< osg::MatrixTransform > graphXTransform = new osg::MatrixTransform();
    graphXTransform->addChild( graphX );
    graphXTransform->addChild( graphXCylinder );
    osg::ref_ptr< osg::MatrixTransform > graphYTransform = new osg::MatrixTransform();
    graphYTransform->addChild( graphY );
    graphYTransform->addChild( graphYCylinder );
    osg::ref_ptr< osg::MatrixTransform > graphZTransform = new osg::MatrixTransform();
    graphZTransform->addChild( graphZ );
    graphZTransform->addChild( graphZCylinder );

    osg::Matrixd matrixTranslateTo0 = osg::Matrixd::translate( -middle.x(), -middle.y(), -middle.z() );
    osg::Matrixd matrixTranslateFrom0 = osg::Matrixd::translate( middle.x(), middle.y(), middle.z() );

    graphXTransform->setMatrix( matrixTranslateTo0 * osg::Matrixd::rotate(
        90.0 * pi() / 180.0,
        osg::Vec3f( 0.0, 1.0, 0.0 ) ) * matrixTranslateFrom0
    );
    graphYTransform->setMatrix( matrixTranslateTo0 * osg::Matrixd::rotate(
        -90.0 * pi() / 180.0,
        osg::Vec3f( 1.0, 0.0, 0.0 ) ) * matrixTranslateFrom0
    );

    groupNode->insert( graphXTransform );
    groupNode->insert( graphYTransform );
    groupNode->insert( graphZTransform );

    return groupNode;
}

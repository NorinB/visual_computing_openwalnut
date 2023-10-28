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

#ifndef WDATASETSINGLE_H
#define WDATASETSINGLE_H

#include <memory>
#include <string>

#include <osg/ref_ptr>

#include "WDataSet.h"
#include "WGrid.h"
#include "WGridRegular3D.h"
#include "WValueSet.h"

class WDataTexture3D;

/**
 * A data set consisting of a set of values based on a grid.
 * \ingroup dataHandler
 */
class WDataSetSingle : public WDataSet // NOLINT
{
public:
    /**
     * Convenience typedef for a std::shared_ptr
     */
    typedef std::shared_ptr< WDataSetSingle > SPtr;

    /**
     * Convenience typedef for a std::shared_ptr; const
     */
    typedef std::shared_ptr< const WDataSetSingle > ConstSPtr;

    /**
     * Constructs an instance out of a value set and a grid.
     *
     * \param newValueSet the value set to use
     * \param newGrid the grid which maps world space to the value set
     */
    WDataSetSingle( std::shared_ptr< WValueSetBase > newValueSet,
                    std::shared_ptr< WGrid > newGrid );

    /**
     * Construct an empty and unusable instance. This is useful for prototypes.
     */
    WDataSetSingle();

    /**
     * Destroys this DataSet instance
     */
    virtual ~WDataSetSingle();

    /**
     * Creates a copy (clone) of this instance but allows one to change the valueset. Unlike copy construction, this is a very useful function if you
     * want to keep the dynamic type of your dataset.
     *
     * \param newValueSet the new valueset.
     * \param newGrid the new grid.
     *
     * \return the clone
     */
    virtual WDataSetSingle::SPtr clone( std::shared_ptr< WValueSetBase > newValueSet, std::shared_ptr< WGrid > newGrid ) const;

    /**
     * Creates a copy (clone) of this instance but allows one to change the valueset. Unlike copy construction, this is a very useful function if you
     * want to keep the dynamic type of your dataset even if you just have a WDataSetSingle.
     *
     * \param newValueSet the new valueset.
     *
     * \return the clone
     */
    virtual WDataSetSingle::SPtr clone( std::shared_ptr< WValueSetBase > newValueSet ) const;

    /**
     * Creates a copy (clone) of this instance but allows one to change the grid. Unlike copy construction, this is a very useful function if you
     * want to keep the dynamic type of your dataset even if you just have a WDataSetSingle.
     *
     * \param newGrid the new grid.
     *
     * \return the clone
     */
    virtual WDataSetSingle::SPtr clone( std::shared_ptr< WGrid > newGrid ) const;

    /**
     * Creates a copy (clone) of this instance. Unlike copy construction, this is a very useful function if you
     * want to keep the dynamic type of your dataset even if you just have a WDataSetSingle.
     *
     * \return the clone
     */
    virtual WDataSetSingle::SPtr clone() const;

    /**
     * \return Reference to its WValueSet
     */
    std::shared_ptr< WValueSetBase > getValueSet() const;

    /**
     * \return Reference to its WGrid
     */
    std::shared_ptr< WGrid > getGrid() const;

    /**
     * Get the scalar value stored at id-th position of the array of the value set. This is the id-th grid position \b only for scalar data sets.
     * \deprecated use getSingleRawValue
     *
     * \param id The id of the value to be obtained
     *
     * \return Scalar value for that given position
     */
    template< typename T >  OW_API_DEPRECATED T getValueAt( size_t id );

    /// @cond Supress doxygen because it produces warning here becuase it does not correctly understand the C++ code.
    /**
     * Get the scalar value stored at id-th position of the array of the value set. This is the id-th grid position \b only for scalar data sets.
     *
     * \param id The id of the value to be obtained
     *
     * \return Scalar value for that given position
     */
    template< typename T >  T getSingleRawValue( size_t id );
    /// @endcond

    /**
     * Get the scalar value stored at id-th position of the array of the value set. This is the id-th grid position \b only for scalar data sets.
     * \deprecated use getSingleRawValue
     *
     * \param id The id of the value to be obtained
     *
     * \return Scalar value for that given position
     */
    double OW_API_DEPRECATED getValueAt( size_t id ) const;

    /**
     * Get the raw scalar value stored at id-th position of the raw array of the value set.
     * This is the value at the id-th \b grid position \b only for scalar data sets.
     *
     * \param id The id of the raw value to be obtained
     *
     * \return Scalar value for that given id
     */
    double getSingleRawValue( size_t id ) const;

    /**
     * Determines whether this dataset can be used as a texture.
     *
     * \return true if usable as texture.
     */
    virtual bool isTexture() const;

    /**
     * Returns the texture representation of the dataset. May throw an exception if no texture is available.
     *
     * \return the texture.
     */
    virtual osg::ref_ptr< WDataTexture3D > getTexture() const;

    /**
     * Gets the name of this prototype.
     *
     * \return the name.
     */
    virtual const std::string getName() const;

    /**
     * Gets the description for this prototype.
     *
     * \return the description
     */
    virtual const std::string getDescription() const;

    /**
     * Returns a prototype instantiated with the true type of the deriving class.
     *
     * \return the prototype.
     */
    static std::shared_ptr< WPrototyped > getPrototype();

protected:
    /**
     * The prototype as singleton.
     */
    static std::shared_ptr< WPrototyped > m_prototype;

    /**
     * Stores the reference of the WGrid of this DataSetSingle instance.
     */
    std::shared_ptr< WGrid > m_grid;

    /**
     * Stores the reference of the WValueSet of this DataSetSingle instance.
     */
    std::shared_ptr< WValueSetBase > m_valueSet;

private:
    /**
     * The 3D texture representing this dataset.
     */
    osg::ref_ptr< WDataTexture3D > m_texture;
};

template< typename T > OW_API_DEPRECATED T WDataSetSingle::getValueAt( size_t id )
{
    return getSingleRawValue< T >( id );
}

template< typename T > T WDataSetSingle::getSingleRawValue( size_t id )
{
    std::shared_ptr< WValueSet< T > > vs = std::dynamic_pointer_cast< WValueSet< T > >( m_valueSet );
    return vs->getScalar( id );
}
#endif  // WDATASETSINGLE_H

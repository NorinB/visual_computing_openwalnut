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

#ifndef WMDATA_H
#define WMDATA_H

#include <memory>
#include <string>
#include <vector>

#include <boost/thread.hpp>

#include "core/kernel/WDataModule.h"

// forward declarations
class WDataSet;
class WDataSetSingle;
class WModuleConnector;
template< class T > class WModuleOutputData;

/**
 * Module for encapsulating WDataSets. It can encapsulate almost everything, but is intended to be used with WDataSets and its
 * inherited classes. This class builds a "source" in OpenWalnut's DataFlow Network.
 * \ingroup modules
 */
class WMData: public WDataModule
{
public:
    /**
     * Default constructor.
     */
    WMData();

    /**
     * Destructor.
     */
    virtual ~WMData();

    /**
     * Gives back the name of this module.
     * \return the module's name.
     */
    virtual const std::string getName() const;

    /**
     * Gives back a description of this module.
     * \return description to module.
     */
    virtual const std::string getDescription() const;

    /**
     * Due to the prototype design pattern used to build modules, this method returns a new instance of this method. NOTE: it
     * should never be initialized or modified in some other way. A simple new instance is required.
     *
     * \return the prototype used to create every module in OpenWalnut.
     */
    virtual std::shared_ptr< WModule > factory() const;

    /**
     * Define a list of file filters we support.
     *
     * \return the list of filters
     */
    virtual std::vector< WDataModuleInputFilter::ConstSPtr > getInputFilter() const;

protected:
    /**
     * \par Description
     * Entry point after loading the module. Runs in separate thread.
     */
    virtual void moduleMain();

    /**
     * Initialize connectors in this function. This function must not be called multiple times for one module instance.
     * The module container manages calling those functions -> so just implement it.
     */
    virtual void connectors();

    /**
     * Initialize properties in this function. This function must not be called multiple times for one module instance.
     * The module container manages calling those functions -> so just implement it. Once initialized the number and type
     * of all properties should be set.
     */
    virtual void properties();

    /**
     * The name of the dataset. Usually the filename.
     */
    WPropString m_dataName;

    /**
     * The basic type of data used in this data set (e.g. float, double, ...)
     */
    WPropString m_dataType;

    /**
     * The name of the dataset type created from the data (e.g. WDataSetScalar, WDataSetVector ...)
     */
    WPropString m_dataSetType;

    /**
     * A list of color map selection types
     */
    std::shared_ptr< WItemSelection > m_matrixSelectionsList;

    /**
     * Selection property for color map
     */
    WPropSelection m_matrixSelection;

    bool m_isTexture; //!< Indicates whether the loaded dataSet will be available as texture.

    /**
     * Called whenever a property changes.
     *
     * \param property the property that has been changed
     */
    void propertyChanged( std::shared_ptr< WPropertyBase > property );

    // in case of a nifti file, there may be several transforms specified in the file
    //! a standard transform (should be an identity transform)
    WMatrix< double > m_transformNoMatrix;

    //! a standard transform (should be an identity transform)
    WMatrix< double > m_transformSForm;

    //! a standard transform (should be an identity transform)
    WMatrix< double > m_transformQForm;

    /**
     * Do the loading.
     */
    void load();

    /**
     * Handle a newly set input. Implement this method to load the newly set input. You can get the input using the \ref getInput and \ref getInputAs
     * methods. Please remember that it is possible to get a NULL pointer here.
     * This happens when the user explicitly sets no input. In this case, you should clean up and reset your output connectors.
     *
     * \note it is very important to NOT load the data inside of this method. It is usually called in the GUI thread. This would block the whole GUI.
     * Instead, use this method for firing a condition, which then wakes your module thread.
     */
    virtual void handleInputChange();

    /**
     * Clean up. Remove props and colormap.
     */
    void cleanUp();
private:
    /**
     * Returns info property group with the three availabe transformation matrixes
     *
     * \return info property group with the three availabe transformation matrixes
     */
    std::shared_ptr< WProperties > getTransformationProperties() const;

    //! a condition for the matrix selection
    std::shared_ptr< WCondition > m_propCondition;

    /**
     * Get a string for the datatype of the given dataset.
     *
     * \param dss the data set whose name should be returned.
     *
     * \return the type name of the specified dataset
     */
    std::string getDataTypeString( std::shared_ptr< WDataSetSingle > dss );

    /**
     * The associated dataset.
     */
    std::shared_ptr< WDataSet > m_dataSet;

    /**
     * The only output of this data module.
     */
    std::shared_ptr< WModuleOutputData< WDataSet > > m_output;

    /**
     * As single. Can be NULL.
     */
    WDataSetSingle::SPtr m_dataSetAsSingle;

    /**
     * Keep track of registered colormaps.
     */
    osg::ref_ptr< WDataTexture3D > m_oldColormap;

    /**
     * Keep track of the old dataset
     */
    std::shared_ptr< WDataSet > m_oldDataSet;

    /**
     * Add the colormapping.
     *
     * \param dataSet the dataset to add
     */
    void updateColorMap( std::shared_ptr< WDataSet > dataSet );

    /**
     * Update matrix.
     */
    void matrixUpdate();

    /**
     * True if the load function needs to be called. Usually set by handleInputChange or the reload trigger
     */
    bool m_reload;
};

#endif  // WMDATA_H

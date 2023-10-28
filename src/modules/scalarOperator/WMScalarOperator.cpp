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

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include <boost/variant.hpp>

#include "WMScalarOperator.h"
#include "WMScalarOperator.xpm"
#include "core/common/WAssert.h"
#include "core/common/WProgress.h"
#include "core/common/WStringUtils.h"
#include "core/common/WTypeTraits.h"
#include "core/common/exceptions/WTypeMismatch.h"
#include "core/dataHandler/WDataHandler.h"
#include "core/dataHandler/WDataHandlerEnums.h"
#include "core/dataHandler/WGridRegular3D.h"
#include "core/dataHandler/exceptions/WDHValueSetMismatch.h"
#include "core/kernel/WKernel.h"

// This line is needed by the module loader to actually find your module.
W_LOADABLE_MODULE( WMScalarOperator )

WMScalarOperator::WMScalarOperator() :
    WModule()
{
    // initialize
}

WMScalarOperator::~WMScalarOperator()
{
    // cleanup
    removeConnectors();
}

std::shared_ptr< WModule > WMScalarOperator::factory() const
{
    return std::shared_ptr< WModule >( new WMScalarOperator() );
}

const char** WMScalarOperator::getXPMIcon() const
{
    return WMScalarOperator_xpm;
}

const std::string WMScalarOperator::getName() const
{
    return "Scalar Operator";
}

const std::string WMScalarOperator::getDescription() const
{
    return "Applies an selected operator on both datasets on a per-voxel basis. Until now, it assumes that both grids are the same.";
}

void WMScalarOperator::connectors()
{
    m_inputA = WModuleInputData< WDataSetScalar >::createAndAdd( shared_from_this(), "operandA", "First operand of operation( A, B )." );
    m_inputB = WModuleInputData< WDataSetScalar >::createAndAdd( shared_from_this(), "operandB", "Second operand of operation( A, B )." );

    m_output = WModuleOutputData< WDataSetScalar >::createAndAdd( shared_from_this(), "result", "Result of voxel-wise operation( A, B )." );

    // call WModules initialization
    WModule::connectors();
}

void WMScalarOperator::properties()
{
    m_propCondition = std::shared_ptr< WCondition >( new WCondition() );

    // create a list of operations here
    m_operations = std::shared_ptr< WItemSelection >( new WItemSelection() );
    m_operations->addItem( "A + B", "Add A to B." );          // NOTE: you can add XPM images here.
    m_operations->addItem( "A - B", "Subtract B from A." );
    m_operations->addItem( "A * B", "Scale A by B." );
    m_operations->addItem( "A / B", "Divide A by B." );
    m_operations->addItem( "abs( A - B )", "Absolute value of A - B." );
    m_operations->addItem( "abs( A )", "Absolute value of A." );
    m_operations->addItem( "clamp( lower, upper, A )", "Clamp A between lower and upper so that l <= A <= u." );
    m_operations->addItem( "A * upper", "Scale data by factor." );
    m_operations->addItem( "Binarize A by upper", "Values > upper, become 1, below or equal become 0" );
    m_operations->addItem( "A + upper", "Add constant value." );

    m_opSelection = m_properties->addProperty( "Operation", "The operation to apply on A and B.", m_operations->getSelectorFirst(),
                                               m_propCondition );
    WPropertyHelper::PC_SELECTONLYONE::addTo( m_opSelection );
    WPropertyHelper::PC_NOTEMPTY::addTo( m_opSelection );

    m_lowerBorder = m_properties->addProperty( "Lower", "Lower border used for clamping.", 0.0, m_propCondition );
    m_lowerBorder->removeConstraint( PC_MIN );
    m_lowerBorder->removeConstraint( PC_MAX );
    m_upperBorder = m_properties->addProperty( "Upper", "Upper border used for clamping.", 1.0, m_propCondition );
    m_upperBorder->removeConstraint( PC_MIN );
    m_upperBorder->removeConstraint( PC_MAX );

    WModule::properties();
}

/**
 * Some math ops.
 */
namespace math
{
    /**
     * Absolute value of the specified parameter.
     * \param u the value for which the absolute value should be returned
     *
     * \return absolute of u
     */
    template < typename T >
    inline T wabs( T u )
    {
        return std::abs( u );
    }

    /**
     * Absolute value of the specified parameter. This is a template specialization for std::abs as 64bit Ints are not supported everywhere.
     *
     * \param u the value for which the absolute value should be returned
     *
     * \return absolute of u
     */
    inline int64_t wabs( int64_t u )
    {
        return u < 0 ? -u : u;
    }

    /**
     * Absolute value of the specified parameter. This is a template specialization for std::abs as it does not allow unsigned types.
     *
     * \param u the value for which the absolute value should be returned
     *
     * \return absolute of u
     */
    inline uint8_t wabs( uint8_t u )
    {
        return u;
    }

    /**
     * Absolute value of the specified parameter. This is a template specialization for std::abs as it does not allow unsigned types.
     *
     * \param u the value for which the absolute value should be returned
     *
     * \return absolute of u
     */
    inline uint16_t wabs( uint16_t u )
    {
        return u;
    }

    /**
     * Absolute value of the specified parameter. This is a template specialization for std::abs as it does not allow unsigned types.
     *
     * \param u the value for which the absolute value should be returned
     *
     * \return absolute of u
     */
    inline uint32_t wabs( uint32_t u )
    {
        return u;
    }

    /**
     * Absolute value of the specified parameter. This is a template specialization for std::abs as it does not allow unsigned types.
     *
     * \param u the value for which the absolute value should be returned
     *
     * \return absolute of u
     */
    inline uint64_t wabs( uint64_t u )
    {
        return u;
    }
}

/**
 * Operator applying some op to both arguments.
 *
 * \tparam T Type of each parameter and the result
 * \param a the first operant
 * \param b the second operant
 *
 * \return result
 */
template< typename T >
inline T opAbsMinus( T a, T b )
{
    return math::wabs( a - b );
}

/**
 * Operator applying some op to both arguments.
 *
 * \tparam T Type of each parameter and the result
 * \param a the first operant
 * \param b the second operant
 *
 * \return result
 */
template< typename T >
inline T opPlus( T a, T b )
{
    return a + b;
}

/**
 * Operator applying some op to both arguments.
 *
 * \tparam T Type of each parameter and the result
 * \param a the first operant
 * \param b the second operant
 *
 * \return result
 */
template< typename T >
inline T opMinus( T a, T b )
{
    return a - b;
}

/**
 * Operator applying some op to both arguments.
 *
 * \tparam T Type of each parameter and the result
 * \param a the first operant
 * \param b the second operant
 *
 * \return result
 */
template< typename T >
inline T opTimes( T a, T b )
{
    return a * b;
}

/**
 * Operator applying some op to both arguments.
 *
 * \tparam T Type of each parameter and the result
 * \param a the first operant
 * \param b the second operant
 *
 * \return result
 */
template< typename T >
inline T opDiv( T a, T b )
{
    return a / b;
}

/**
 * Operator applying some op to argument.
 *
 * \tparam T Type of each parameter and the result
 * \param a the first operant
 * \param l lower border
 * \param u upper border
 *
 * \return result
 */
template< typename T >
inline T opAbs( T a, T /* l */, T /* u */ )
{
    return math::wabs( a );
}

/**
 * Operator binarizing some op with certain threshold.
 *
 * \tparam T Type of each parameter and the result
 * \param a the value to binarize
 * \param l lower border
 * \param u upper border, used to decied if value greater becomes one or beneath or equal becomes 0.
 *
 * \return result
 */
template< typename T >
inline T opBinarizeByA( T a, T /* l */, T u )
{
  return ( a > u ) ? 1 : 0;
}

/**
 * Operator clamping argument.
 *
 * \tparam T Type of each parameter and the result
 * \param a the first operant
 * \param l lower border
 * \param u upper border
 *
 * \return result
 */
template< typename T >
inline T opClamp( T a, T l, T u )
{
    T uclamp = a > u ? u : a;
    return uclamp < l ? l : uclamp;
}

/**
 * Operator adding value to argument.
 *
 * \tparam T Type of each parameter and the result
 * \param v the first operant
 * \param l ignored
 * \param u scaler
 *
 * \return result
 */

template< typename T >
inline T opAddToA( T v, T /* l */, T u )
{
    return v + u;
}
/**
 * Operator applying some op to argument.
 *
 * \tparam T Type of each parameter and the result
 * \param v the first operant
 * \param l ignored
 * \param u costant value to add
 *
 * \return result
 */
template< typename T >
inline T opScaleByA( T v, T /* l */, T u )
{
    return v * u;
}

template< typename VSetAType >
WMScalarOperator::VisitorVSetB< VSetAType >::VisitorVSetB( const WValueSet< VSetAType >* const vsetA, size_t opIdx ):
    boost::static_visitor< result_type >(),
    m_vsetA( vsetA ),
    m_opIdx( opIdx )
{
}

/**
 * Visitor on the second valueset. This applies the operation.
 *
 * \tparam VSetBType the integral type of the currently visited valueset.
 * \param vsetB the valueset currently visited (B).
 *
 * \return the result of o(A,B)
 */
template< typename VSetAType >
template< typename VSetBType >
boost::static_visitor< std::shared_ptr< WValueSetBase > >::result_type WMScalarOperator::VisitorVSetB< VSetAType >::operator()(
    const WValueSet< VSetBType >* const& vsetB ) const      // NOLINT
{
    // get best matching return scalar type
    typedef typename WTypeTraits::TypePromotion< VSetAType, VSetBType >::Result ResultT;

    size_t order = m_vsetA->order();
    size_t dim = m_vsetA->dimension();
    dataType type = DataType< ResultT >::type;
    std::vector< ResultT > data;
    data.resize( m_vsetA->rawSize() );

    // discriminate the right operation with the correct type. It would be nicer to use some kind of strategy pattern here, but the template
    // character of the operators forbids it as template methods can't be virtual. Besides this, at some point in the module main the
    // selector needs to be queried and its index mapped to a pointer. This is what we do here.
    boost::function< ResultT( ResultT, ResultT ) > op;
    switch( m_opIdx )
    {
        case 1:
            op = &opMinus< ResultT >;
            break;
        case 2:
            op = &opTimes< ResultT >;
            break;
        case 3:
            op = &opDiv< ResultT >;
            break;
        case 4:
            op = &opAbsMinus< ResultT >;
            break;
        case 0:
        default:
            op = &opPlus< ResultT >;
            break;
    }

    // apply op to each value
    const VSetAType* a = m_vsetA->rawData();
    const VSetBType* b =   vsetB->rawData();
    for( size_t i = 0; i < m_vsetA->rawSize(); ++i )
    {
        data[ i ] = op( static_cast< ResultT >( a[ i ] ), static_cast< ResultT >( b[ i ] ) );
    }

    // create result value set
    std::shared_ptr< WValueSet< ResultT > > result = std::shared_ptr< WValueSet< ResultT > >(
        new WValueSet< ResultT >( order,
                                dim,
                                std::shared_ptr< std::vector< ResultT > >( new std::vector< ResultT >( data ) ),
                                type )
    );
    return result;
}


WMScalarOperator::VisitorVSetA::VisitorVSetA( WValueSetBase* vsetB, size_t opIdx ):
    boost::static_visitor< result_type >(),
    m_vsetB( vsetB ),
    m_opIdx( opIdx )
{
}

/**
 * Called by boost::varying during static visiting. Creates a new VisitorVSetB which finally applies the operation.
 *
 * \tparam T the real integral type of the first value set.
 * \param vsetA the first valueset currently visited.
 *
 * \return the result from the operation with this and the second value set
 */
template < typename T >
boost::static_visitor< std::shared_ptr< WValueSetBase > >::result_type WMScalarOperator::VisitorVSetA::operator()(
    const WValueSet< T >* const& vsetA ) const             // NOLINT
{
    // visit the second value set as we now know the type of the first one
    VisitorVSetB< T > visitor( vsetA, m_opIdx );
    return m_vsetB->applyFunction( visitor );
}

WMScalarOperator::VisitorVSetSingleArgument::VisitorVSetSingleArgument( size_t opIdx ):
    boost::static_visitor< result_type >(),
    m_opIdx( opIdx )
{
}

/**
 * Called by boost::varying during static visiting. Applies the operation to it
 *
 * \tparam T the real integral type of the first value set.
 * \param vsetA the first valueset currently visited.
 *
 * \return the result from the operation with this and the second value set
 */
template < typename T >
boost::static_visitor< std::shared_ptr< WValueSetBase > >::result_type WMScalarOperator::VisitorVSetSingleArgument::operator()(
    const WValueSet< T >* const& vsetA ) const             // NOLINT
{
    // get best matching return scalar type
    typedef T ResultT;

    size_t order = vsetA->order();
    size_t dim = vsetA->dimension();
    dataType type = DataType< ResultT >::type;
    std::vector< ResultT > data;
    data.resize( vsetA->rawSize() );

    // discriminate the right operation with the correct type. It would be nicer to use some kind of strategy pattern here, but the template
    // character of the operators forbids it as template methods can't be virtual. Besides this, at some point in the module main the
    // selector needs to be queried and its index mapped to a pointer. This is what we do here.
    boost::function< ResultT( ResultT, ResultT l, ResultT u ) > op;
    switch( m_opIdx )
    {
        case 5:
            op = &opAbs< ResultT >;
            break;
        case 6:
            op = &opClamp< ResultT >;
            break;
        case 7:
            op = &opScaleByA< ResultT >;
            break;
        case 8:
            op = &opBinarizeByA< ResultT >;
            break;
        case 9:
            op = &opAddToA< ResultT >;
            break;
        default:
            op = &opAbs< ResultT >;
            break;
    }

    // apply op to each value
    const T* a = vsetA->rawData();
    for( size_t i = 0; i < vsetA->rawSize(); ++i )
    {
        data[ i ] = op( a[ i ], m_lowerBorder, m_upperBorder );
    }

    // create result value set
    std::shared_ptr< WValueSet< ResultT > > result = std::shared_ptr< WValueSet< ResultT > >(
        new WValueSet< ResultT >( order,
                                    dim,
                                    std::shared_ptr< std::vector< ResultT > >( new std::vector< ResultT >( data ) ),
                                    type )
    );
    return result;
}

void WMScalarOperator::VisitorVSetSingleArgument::setBorder( double l, double u )
{
    m_lowerBorder = l;
    m_upperBorder = u;
}

void WMScalarOperator::moduleMain()
{
    // let the main loop awake if the data changes or the properties changed.
    m_moduleState.setResetable( true, true );
    m_moduleState.add( m_inputA->getDataChangedCondition() );
    m_moduleState.add( m_inputB->getDataChangedCondition() );
    m_moduleState.add( m_propCondition );

    // signal ready state
    ready();

    // loop until the module container requests the module to quit
    while( !m_shutdownFlag() )
    {
        // Now, the moduleState variable comes into play. The module can wait for the condition, which gets fired whenever the input receives data
        // or an property changes. The main loop now waits until something happens.
        debugLog() << "Waiting ...";
        m_moduleState.wait();

        // woke up since the module is requested to finish
        if( m_shutdownFlag() )
        {
            break;
        }

        bool propsChanged = m_lowerBorder->changed() || m_upperBorder->changed();

        // has the data changed?
        if( m_opSelection->changed() || propsChanged || m_inputA->handledUpdate() || m_inputB->handledUpdate() )
        {
            std::shared_ptr< WDataSetScalar > dataSetA = m_inputA->getData();
            std::shared_ptr< WDataSetScalar > dataSetB = m_inputB->getData();
            if( !dataSetA )
            {
                // reset output if input was reset/disconnected
                debugLog() << "Resetting output.";
                m_output->reset();
                continue;
            }

            // the first value-set is always needed -> grab it
            std::shared_ptr< WValueSetBase > valueSetA = dataSetA->getValueSet();

             // use a custom progress combiner
            std::shared_ptr< WProgress > prog = std::shared_ptr< WProgress >(
                new WProgress( "Applying operator on data" ) );
            m_progress->addSubProgress( prog );

            // apply the operation to each voxel
            debugLog() << "Processing ...";

            // kind of operation?
            WItemSelector s = m_opSelection->get( true );

            // this keeps the result
            std::shared_ptr< WValueSetBase > newValueSet;

            // single operand operation?
            if( ( s == 5 ) || ( s == 6 ) || ( s == 7 ) || ( s == 8 ) || ( s == 9 ) )
            {
                VisitorVSetSingleArgument visitor( s );    // the visitor cascades to the second value set
                visitor.setBorder( m_lowerBorder->get( true ), m_upperBorder->get( true ) );
                newValueSet = valueSetA->applyFunction( visitor );

                // Create the new dataset and export it
                m_output->updateData( std::shared_ptr<WDataSetScalar>( new WDataSetScalar( newValueSet, m_inputA->getData()->getGrid() ) ) );
            }
            else  // multiple operands:
            {
                // valid data?
                if( dataSetB )
                {
                    std::shared_ptr< WValueSetBase > valueSetB = dataSetB->getValueSet();

                    // both value sets need to be the same
                    bool match = ( valueSetA->dimension() == valueSetB->dimension() ) &&
                                 ( valueSetA->order() == valueSetB->order() ) &&
                                 ( valueSetA->rawSize() == valueSetB->rawSize() );
                    if( !match )
                    {
                        throw WDHValueSetMismatch( std::string( "The two value sets are not of equal size, dimension and order." ) );
                    }

                    VisitorVSetA visitor( valueSetB.get(), s );    // the visitor cascades to the second value set
                    newValueSet = valueSetA->applyFunction( visitor );

                    // Create the new dataset and export it
                    m_output->updateData( std::shared_ptr<WDataSetScalar>( new WDataSetScalar( newValueSet, m_inputA->getData()->getGrid() ) ) );
                }
                else
                {
                    // reset output if input was reset/disconnected
                    debugLog() << "Resetting output.";
                    m_output->reset();

                    // remove progress too
                    prog->finish();
                    m_progress->removeSubProgress( prog );

                    continue;
                }
            }

            // done
            prog->finish();
            m_progress->removeSubProgress( prog );
        }
    }
}


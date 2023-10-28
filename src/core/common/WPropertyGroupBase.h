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

#ifndef WPROPERTYGROUPBASE_H
#define WPROPERTYGROUPBASE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include "WConditionSet.h"
#include "WPropertyBase.h"
#include "WPropertyTypes.h"
#include "WPropertyVariable.h"
#include "WSharedSequenceContainer.h"

/**
 * This is the base class and interface for property groups. This class itself is abstract and derived from WPropertyBase. So if you create a
 * group of properties, this ensures that your group is a property itself. This interface defines no way to add, remove or edit the property list
 * itself. This allows the deriving class to prohibit modifications and to provide a custom interface, or even model-controller like
 * implementations.
 *
 * Another advantage is, that the GUI implementations which support WPropertyGroupBase can display your custom properties directly.
 */
class WPropertyGroupBase: public WPropertyBase
{
public:
    /**
     * For shortening: a type defining a shared vector of WSubject pointers.
     */
    typedef std::vector< std::shared_ptr< WPropertyBase > > PropertyContainerType;

    /**
     * The alias for a shared container.
     */
    typedef WSharedSequenceContainer< PropertyContainerType > PropertySharedContainerType;

    /**
     * The const iterator type of the container.
     */
    typedef PropertyContainerType::const_iterator PropertyConstIterator;

    /**
     * The iterator type of the container.
     */
    typedef PropertyContainerType::iterator PropertyIterator;

    /**
     * Convenience typedef for a std::shared_ptr< WPropertyGroupBase >.
     */
    typedef std::shared_ptr< WPropertyGroupBase > SPtr;

    /**
     * Convenience typedef for a std::shared_ptr< const WPropertyGroupBase >.
     */
    typedef std::shared_ptr< const WPropertyGroupBase > ConstSPtr;

    /**
     * The separator used to separate groups and subgroups
     */
    static const std::string separator;

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // Construction
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor. Creates an empty list of properties.
     *
     * \param name the name of the property group. The GUI is using this name for naming the tabs/group boxes
     * \param description the description of the group.
     */
    WPropertyGroupBase( std::string name, std::string description );

    /**
     * Copy constructor. Creates a deep copy of this property. As boost::signals2 and condition variables are non-copyable, new instances get
     * created. The subscriptions to a signal are LOST as well as all listeners to a condition.
     * The conditions you can grab using getValueChangeConditon and getCondition are not the same as in the original! This is because
     * the class corresponds to the observer/observable pattern. You won't expect a clone to fire a condition if a original flag is changed
     * (which after cloning is completely decoupled from the clone).
     *
     * \note the properties inside this list are also copied deep
     *
     * \param from the instance to copy.
     */
    explicit WPropertyGroupBase( const WPropertyGroupBase& from );

    /**
     * Destructor.
     */
    virtual ~WPropertyGroupBase();

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // The WPropertyGroupBase interface
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Helper function that finds a property by its name. Use this method to find out whether the property exists or not, since
     * findProperty throws an exception.
     *
     * \param name name of searched property.
     *
     * \return Answer to the question whether the property exists.
     */
    virtual bool existsProperty( std::string name );

    /**
     * Function searches the property. If it does not exists, it throws an exception.
     *
     * \param name the name of the property
     *
     * \return a WProperty object
     */
    virtual std::shared_ptr< WPropertyBase > getProperty( std::string name );

    /**
     * Returns a read ticket for read-access to the list of properties.
     *
     * \return the read ticket.
     */
    virtual PropertySharedContainerType::ReadTicket getProperties() const;

    /**
     * Returns an read ticket for the properties. This, and only this, has to be used for external iteration of properties.
     *
     * \see WSharedObjectTicketRead
     * \return the read ticket.
     */
    virtual PropertySharedContainerType::ReadTicket getReadTicket() const;

    /**
     * Searches the property with a given name. It does not throw any exception. It simply returns NULL if it can't be found. It searches
     * in nested groups too. The naming rules for finding a property in subgroups of this group is like specifying a path, using the \ref
     * separator char: "somegroup" + separator + "anothergroup" + separator + "propnametosearch".
     *
     * \param name the name of the property to search
     *
     * \return the property or NULL if not found.
     */
    virtual std::shared_ptr< WPropertyBase > findProperty( std::string name ) const;

    /**
     * The visitor type used to visit properties as strings. The first parameter is the name, including the path of the property, relative to
     * this group. The second parameter is the value as string.
     */
    typedef boost::function< void ( std::string, std::string )> PropertyStringVisitor;

    /**
     * Visit all leafs in the property three that aren't empty groups. This is especially interesting when using it with lambda functionality.
     * The visitor function gets two parameters: 1st: the name of the property, including the path beginning at this group; 2nd: the value as
     * string.
     *
     * \param visitor the function to use for each property.
     * \param pathPrefix add this prefix to the property name in the visitor. It might be interesting if manually implementing group visitors
     * that always require a complete path, so you can add an upper-level path here.
     */
    virtual void visitAsString( PropertyStringVisitor visitor, std::string pathPrefix = "" ) const;

    /**
     * Checks whether the property group should be hidden if it is empty.
     *
     * \return true if it should be hidden if empty.
     */
    bool autoHideEmpty() const;

    /**
     * Should the property group be hidden automatically if it is empty? By default, this is true.
     *
     * \note this does not trigger an update. You should use this setting before adding this property to a parent group.
     *
     * \param autoHide true if it should be hidden automatically if empty.
     */
    void setAutoHideEmpty( bool autoHide = true );
protected:
   /**
    * Helping function to find a property inside a specific group. It does not recursively find properties nested inside other property groups.
    *
    * \param props the group to search in. This is not a shared pointer since it is not needed. It simply can't happen that it is freed during
    * findProperty as it is contained in this or a nested properties instance.
    * \param name the name of the property inside THIS group.
    *
    * \return the property if found, else NULL.
    */
    virtual std::shared_ptr< WPropertyBase > findProperty( const WPropertyGroupBase* const props, std::string name ) const;

    /**
     * The set of proerties. This uses the operators ==,<,> WProperty to determine equalness.
     */
    PropertySharedContainerType m_properties;

    /**
     * Compares the names of two properties and returns true if they are equal.
     *
     * \param prop1 the first prop.
     * \param prop2 the second prop.
     *
     * \return Are the names of the two properties equal?
     */
    bool propNamePredicate( std::shared_ptr< WPropertyBase > prop1, std::shared_ptr< WPropertyBase > prop2 ) const;

    /**
     * Insert the specified property into the list. This method is protected. It is a convenience method for deriving classes to add properties
     * without the need to update several conditions and similar.
     *
     * \param prop the property to add
     */
    void addArbitraryProperty( WPropertyBase::SPtr prop );

    /**
     * Comfortable template to create a property instance and add it to the group. This is a utility for deriving classes which need to handle
     * certain property types and other types during compile time.
     *
     * At the first glance, this might not look very useful. But this
     * is practical to change the add-behaviour for certain property types by specializing this class. For example, the template \ref
     * WPropertyStruct uses this to modify the behaviour for the non-property type \ref WPropertyStructHelper::NOTYPE, which is used as
     * template list default (to emulate variadic template parameters lists).
     *
     * \tparam PropertyType the property type to create. It is assumed that this is a shared_ptr< WPropertyXYZ >.
     */
    template< typename PropertyType >
    struct PropertyCreatorAndGroupAdder
    {
        /**
         * The type of the initial value.
         */
        typedef typename PropertyType::element_type::ValueType ValueType;

        /**
         * Actually does the work and adds a new property with the given name, description and other parameters to the specified group.
         *
         * \param group the group to add the new property to
         * \param name the name of the new property
         * \param description the description of the new property
         * \param initial initial value
         */
        static void createAndAdd( WPropertyGroupBase* group, std::string name, std::string description, const ValueType& initial = ValueType() )
        {
            group->addArbitraryProperty(
                PropertyType(
                    new typename PropertyType::element_type( name, description, initial )
                )
            );
       }
    };

private:
    /**
     * True if the prop should be hidden if if empty.
     */
    bool m_autoHideEmpty;
};

#endif  // WPROPERTYGROUPBASE_H


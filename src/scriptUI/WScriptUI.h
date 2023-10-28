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

#ifndef WSCRIPTUI_H
#define WSCRIPTUI_H

#include <string>

#include <boost/program_options.hpp>

#include "core/ui/WUI.h"

/**
 * \class WScriptUI
 *
 * Implements a UI that executes scripts. These can be read from files or input by the user,
 * depending on the parameters supplied to the executable.
 *
 * \ingroup ui
 */
class WScriptUI : public WUI
{
public:
    /**
     * Constructor.
     *
     * \param argc number of arguments given on command line.
     * \param argv arguments given on command line.
     * \param options The program options.
     */
    WScriptUI( int argc, char** argv, boost::program_options::variables_map const& options );

    /**
     * Destructor.
     */
    virtual ~WScriptUI();

    /**
     * Runs the UI.
     *
     * \return the return code.
     */
    virtual int run();

    /**
     * Returns the widget factory of the UI. The Script UI always returns NULL as it does not support widgets. The WUIRequirement checks for this
     * too and thus disallows modules using WUI.
     *
     * \return the factory. Use this to create your widget instances.
     */
    virtual WUIWidgetFactory::SPtr getWidgetFactory() const;

protected:
    /**
     * If you need to load additional modules from your toolboxes, you might want specify these paths in a config file.
     * In that file we need a line starting with: "additionalModulePaths=" followed by a comma separated list of paths.
     * Please note this is the same format as in the config.qt4gui file, so you may symlink it.
     *
     * \param configPath This is the path to the config file. If not existent, nothing will be thrown or done.
     */
    virtual void loadToolboxes( boost::filesystem::path configPath );

    //! The programm options.
    boost::program_options::variables_map const& m_programOptions;
};

#endif  // WSCRIPTUI_H

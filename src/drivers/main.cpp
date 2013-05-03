// Copyright (C) 2011 Technische Universitaet Muenchen
// This file is part of the preCICE project. For conditions of distribution and
// use, please see the license notice at http://www5.in.tum.de/wiki/index.php/PreCICE_License
#include "utils/Globals.hpp"
#include "tarch/logging/Log.h"
#include "utils/Parallel.hpp"
#include "boost/foreach.hpp"
#include "tarch/configuration/ConfigurationRegistry.h"
#include "tarch/configuration/TopLevelConfiguration.h"
#include "tarch/logging/CommandLineLogger.h"
#include "precice/impl/SolverInterfaceImpl.hpp"
#include "precice/config/Configuration.hpp"
#include <iostream>

void printUsage()
{
  std::cout << "Usage:" << std::endl << std::endl;
  std::cout << "Run tests          :  ./binprecice test ConfigurationName PathToSrc" << std::endl;
  std::cout << "Run server         :  ./binprecice server ParticipantName ConfigurationName" << std::endl;
  std::cout << "Print XML reference:  ./binprecice xml Linewidth" << std::endl;
}

int main ( int argc, char** argv )
{
  // By default, debuggin is turned on with a filter list entry. This removes
  // entry and turns off all debug messages until configuration.
  using namespace tarch::logging;
  CommandLineLogger::getInstance().clearFilterList();
  CommandLineLogger::FilterListEntry filter("", true); // All off
  CommandLineLogger::getInstance().addFilterListEntry(filter);

  using namespace tarch::configuration;
  tarch::logging::Log log("");
# ifndef PRECICE_NO_MPI
  MPI_Init(&argc, &argv); // To prevent auto-init/finalization by preCICE
# endif
  precice::utils::Parallel::initialize(&argc, &argv, "");
  bool runTests = false;
  bool runServer = false;
  bool runHelp = false;

  bool wrongParameters = false;
  if (argc == 3){
    if (std::string(argv[1]) == std::string("xml")){
      runHelp = true;
    }
    else {
      wrongParameters = true;
    }
  }
  else if (argc == 4){
    if ( std::string(argv[1]) == std::string("server") ){
      runServer = true;
    }
    else if ( std::string(argv[1]) == std::string("test") ){
      runTests = true;
    }
    else {
      wrongParameters = true;
    }
  }
  else {
    wrongParameters = true;
  }

  if (wrongParameters){
    printUsage();
    return 1;
  }

  if (runTests){
    assertion(not runServer);
    assertion(not runHelp);
    std::cout << "PreCICE running tests..." << std::endl;
    std::string configFile(argv[2]);
    precice::utils::Globals::setPathToSources(argv[3]);
    std::cout << "   Configuration file = " << configFile << std::endl;
    std::cout << "   Path to sources = " << argv[3] << std::endl;
    std::list<TopLevelConfiguration*> configs =
        ConfigurationRegistry::getInstance().readFile( configFile, "configuration" );
    if (configs.empty()) {
      log.error( "main()", "config file " + configFile + " not found or invalid!" );
      return 1;
    }
    foreach ( TopLevelConfiguration* config, configs ){
      config->interpreteConfiguration();
    }
    ConfigurationRegistry::getInstance().freeConfigurations(configs);
  }
  else if ( runServer ){
    assertion(not runTests);
    assertion(not runHelp);
    std::cout << "PreCICE running server..." << std::endl;
    std::string participantName ( argv[2] );
    std::string configFile ( argv[3] );
    std::cout << "  Participant = " << participantName << std::endl;
    std::cout << "  Configuration = " << configFile << std::endl;
    int size = precice::utils::Parallel::getCommunicatorSize();
    if ( size != 1 ){
      log.error( "main()", "Server can be run with only one process!" );
    }
    precice::impl::SolverInterfaceImpl server ( participantName, 0, 1, true );
    server.configure(configFile);
    server.runServer();
    std::cout << std::endl << std::endl << "...finished running server" << std::endl;
  }
  else if (runHelp){
    assertion(not runServer);
    assertion(not runTests);
    int linewidth = atoi(argv[2]);
    //CommandLineLogger::FilterListEntry filter2("debug", false); // debug on
    //CommandLineLogger::getInstance().addFilterListEntry(filter2);
    std::cout << "<?xml version=\"1.0\"?>" << std::endl << std::endl
              << "<!-- preCICE XML configuration reference"
              << std::endl << std::endl
              << "     Configuration outline:"     << std::endl << std::endl
              << "     <precice-configuration>"    << std::endl
              << "        <log-filter .../>"       << std::endl
              << "        <log-output .../>"       << std::endl
              << "        <solver-interface>"      << std::endl
              << "           <data .../>"          << std::endl
              << "           <spacetree .../>"     << std::endl
              << "           <mesh .../>"          << std::endl
              << "           <geometry .../>"      << std::endl
              << "           <participant .../>"   << std::endl
              << "           <communication .../>" << std::endl
              << "           <coupling-scheme .../>" << std::endl
              << "        </solverInterface>"      << std::endl
              << "     </precice-configuration>"   << std::endl << std::endl
              << "     Configuration reference: -->" << std::endl << std::endl;
    precice::config::Configuration config;
    std::cout << config.getXMLTag().printDocumentation(linewidth, 0) << std::endl << std::endl;
    //std::cout << "...finished printing XML documentation" << std::endl;
  }
  else {
    assertion ( false );
  }
  precice::utils::Parallel::finalize();
# ifndef PRECICE_NO_MPI
  MPI_Finalize(); // Reason: see MPI_Init() at beginning of main()
# endif
  return 0;
}


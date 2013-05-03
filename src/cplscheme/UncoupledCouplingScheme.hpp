// Copyright (C) 2011 Technische Universitaet Muenchen
// This file is part of the preCICE project. For conditions of distribution and
// use, please see the license notice at http://www5.in.tum.de/wiki/index.php/PreCICE_License
#ifndef PRECICE_CPLSCHEME_UNCOUPLEDCOUPLINGSCHEME_HPP_
#define PRECICE_CPLSCHEME_UNCOUPLEDCOUPLINGSCHEME_HPP_

#include "CouplingScheme.hpp"
#include "tarch/logging/Log.h"

// ----------------------------------------------------------- CLASS DEFINITION

namespace precice {
namespace cplscheme {

class UncoupledCouplingScheme : public CouplingScheme
{
public:

  /**
   * @brief Constructor.
   */
  UncoupledCouplingScheme (
    double             maxTime,
    int                maxTimesteps,
    int                validDigits,
    const std::string& participant );

  /**
   * @brief Destructor, virtual because of virtual functions.
   */
  virtual ~UncoupledCouplingScheme() {}

  /**
   * @brief Initializes the coupling scheme.
   *
   * Sets up communication to coupling partner, initializes coupling state.
   */
  virtual void initialize (
    double startTime,
    int    startTimestep );

  /**
   * @brief Empty, since this scheme has no data.
   */
  virtual void initializeData();

  /**
   * @brief Adds newly computed time. Has to be called before every advance.
   */
  virtual void addComputedTime ( double timeToAdd );

  /**
   * @brief Advances within the coupling scheme.
   */
  virtual void advance();

  /**
   * @brief Empty, since nothing to finalize.
   */
  virtual void finalize();

  /*
   * @brief returns list of all coupling partners
   */
  virtual std::vector<std::string> getCouplingPartners (
    const std::string& accessorName ) const;

  virtual void sendState (
    com::PtrCommunication communication,
    int                   rankReceiver );

  virtual void receiveState (
    com::PtrCommunication communication,
    int                   rankSender );

  virtual std::string printCouplingState() const;

  virtual void exportState(io::TXTWriter& writer) const {}

  virtual void importState(io::TXTReader& reader) {}

private:

  // @brief Logging device.
  static tarch::logging::Log _log;

  // @brief Name of participant starting the explicit coupling scheme.
  std::string _participant;
};

}} // namespace precice, cplscheme

#endif /* PRECICE_CPLSCHEME_UNCOUPLEDCOUPLINGSCHEME_HPP_ */

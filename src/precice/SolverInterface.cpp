// Copyright (C) 2011 Technische Universitaet Muenchen
// This file is part of the preCICE project. For conditions of distribution and
// use, please see the license notice at http://www5.in.tum.de/wiki/index.php/PreCICE_License
#include "precice/SolverInterface.hpp"
#include "precice/impl/SolverInterfaceImpl.hpp"
#include "tarch/la/WrappedVector.h"
#include "utils/Globals.hpp"

namespace precice {

using namespace tarch::la;

SolverInterface:: SolverInterface
(
  const std::string& accessorName,
  int                solverProcessIndex,
  int                solverProcessSize )
:
  _impl ( new impl::SolverInterfaceImpl(accessorName, solverProcessIndex,
                                        solverProcessSize, false) )
{}

SolverInterface:: ~SolverInterface()
{
  assertion ( _impl != NULL );
  delete _impl;
}

void SolverInterface:: configure
(
  const std::string& configurationFileName )
{
  _impl->configure ( configurationFileName );
}

double SolverInterface:: initialize()
{
  return _impl->initialize();
}

void SolverInterface:: initializeData()
{
  _impl->initializeData();
}

double SolverInterface:: advance
(
  double computedTimestepLength )
{
  return _impl->advance ( computedTimestepLength );
}

void SolverInterface:: finalize()
{
  return _impl->finalize();
}

int SolverInterface:: getDimensions() const
{
  return _impl->getDimensions();
}

bool SolverInterface:: isCouplingOngoing()
{
  return _impl->isCouplingOngoing();
}

bool SolverInterface:: isReadDataAvailable()
{
  return _impl->isReadDataAvailable();
}

bool SolverInterface:: isWriteDataRequired
(
  double computedTimestepLength )
{
  return _impl->isWriteDataRequired(computedTimestepLength);
}

bool SolverInterface:: isTimestepComplete()
{
  return _impl->isTimestepComplete();
}

bool SolverInterface:: isActionRequired
(
  const std::string& action )
{
  return _impl->isActionRequired ( action );
}

void SolverInterface:: fulfilledAction
(
  const std::string& action )
{
  _impl->fulfilledAction ( action );
}

bool SolverInterface:: hasMesh
(
  const std::string& meshName ) const
{
  return _impl->hasMesh ( meshName );
}

int SolverInterface:: getMeshID
(
  const std::string& meshName )
{
  return _impl->getMeshID ( meshName );
}

std::set<int> SolverInterface:: getMeshIDs()
{
  return _impl->getMeshIDs();
}

bool SolverInterface:: hasData
(
  const std::string& dataName ) const
{
  return _impl->hasData ( dataName );
}

int SolverInterface:: getDataID
(
  const std::string& dataName )
{
  return _impl->getDataID ( dataName );
}

int SolverInterface:: inquirePosition
(
  const double*        point,
  const std::set<int>& meshIDs )
{
  return _impl->inquirePosition ( point, meshIDs );
}

ClosestMesh SolverInterface:: inquireClosestMesh
(
  const double*        point,
  const std::set<int>& meshIDs )
{
  return _impl->inquireClosestMesh ( point, meshIDs );
}

VoxelPosition SolverInterface:: inquireVoxelPosition
(
  const double*        voxelCenter,
  const double*        voxelHalflengths,
  bool                 includeBoundaries,
  //bool                 storeContent,
  const std::set<int>& meshIDs )
{
  return _impl->inquireVoxelPosition ( voxelCenter, voxelHalflengths,
                                       includeBoundaries, meshIDs );
}

void SolverInterface:: resetWritePositions
(
  int meshID )
{
  _impl->resetWritePositions(meshID);
}

void SolverInterface:: resetReadPositions
(
  int meshID )
{
  _impl->resetReadPositions(meshID);
}

int SolverInterface:: setWritePosition
(
  int           meshID,
  const double* position )
{
  return _impl->setWritePosition(meshID, position);
}

void SolverInterface:: setWritePositions
(
  int     meshID,
  int     size,
  double* positions,
  int*    ids )
{
  _impl->setWritePositions(meshID, size, positions, ids);
}

void SolverInterface:: getWritePositions
(
  int     meshID,
  int     size,
  int*    ids,
  double* positions )
{
  _impl->getWritePositions(meshID, size, ids, positions);
}

void SolverInterface:: getWriteIDsFromPositions
(
  int     meshID,
  int     size,
  double* positions,
  int*    ids )
{
  _impl->getWriteIDsFromPositions(meshID, size, positions, ids);
}

int SolverInterface:: getWriteNodesSize ( int meshID )
{
  return _impl->getWriteNodesSize(meshID);
}

int SolverInterface:: setReadPosition
(
  int           meshID,
  const double* position )
{
  return _impl->setReadPosition(meshID, position);
}

void SolverInterface:: setReadPositions
(
  int     meshID,
  int     size,
  double* positions,
  int*    ids )
{
  _impl->setReadPositions(meshID, size, positions, ids);
}

void SolverInterface:: getReadPositions
(
  int     meshID,
  int     size,
  int*    ids,
  double* positions )
{
  _impl->getReadPositions(meshID, size, ids, positions);
}

void SolverInterface:: getReadIDsFromPositions
(
  int     meshID,
  int     size,
  double* positions,
  int*    ids )
{
  _impl->getReadIDsFromPositions(meshID, size, positions, ids);
}

int SolverInterface:: getReadNodesSize ( int meshID )
{
  return _impl->getReadNodesSize(meshID);
}

int SolverInterface:: setMeshVertex
(
  int           meshID,
  const double* position )
{
  return _impl->setMeshVertex ( meshID, position );
}

int SolverInterface:: setMeshEdge
(
  int meshID,
  int firstVertexID,
  int secondVertexID )
{
  return _impl->setMeshEdge ( meshID, firstVertexID, secondVertexID );
}

void SolverInterface:: setMeshTriangle
(
  int meshID,
  int firstEdgeID,
  int secondEdgeID,
  int thirdEdgeID )
{
  _impl->setMeshTriangle ( meshID, firstEdgeID, secondEdgeID, thirdEdgeID );
}

void SolverInterface:: setMeshTriangleWithEdges
(
  int meshID,
  int firstVertexID,
  int secondVertexID,
  int thirdVertexID )
{
  _impl->setMeshTriangleWithEdges ( meshID, firstVertexID, secondVertexID, thirdVertexID );
}

void SolverInterface:: setMeshQuad
(
  int meshID,
  int firstEdgeID,
  int secondEdgeID,
  int thirdEdgeID,
  int fourthEdgeID )
{
  _impl->setMeshQuad(meshID, firstEdgeID, secondEdgeID, thirdEdgeID, fourthEdgeID);
}

void SolverInterface:: setMeshQuadWithEdges
(
  int meshID,
  int firstVertexID,
  int secondVertexID,
  int thirdVertexID,
  int fourthVertexID )
{
  _impl->setMeshQuadWithEdges(meshID, firstVertexID, secondVertexID, thirdVertexID,
                              fourthVertexID);
}

void SolverInterface:: mapWrittenData
(
  int meshID )
{
  _impl->mapWrittenData(meshID);
}

void SolverInterface:: mapReadData
(
  int meshID )
{
  _impl->mapReadData(meshID);
}


void SolverInterface:: writeBlockVectorData
(
  int     dataID,
  int     size,
  int*    valueIndices,
  double* values )
{
  _impl->writeBlockVectorData(dataID, size, valueIndices, values);
}

void SolverInterface:: writeVectorData
(
  int           dataID,
  int           valueIndex,
  const double* value )
{
  _impl->writeVectorData(dataID, valueIndex, value);
}

void SolverInterface:: writeScalarData
(
  int    dataID,
  int    valueIndex,
  double value )
{
  _impl->writeScalarData ( dataID, valueIndex, value );
}

void SolverInterface:: readBlockVectorData
(
  int     dataID,
  int     size,
  int*    valueIndices,
  double* values )
{
  _impl->readBlockVectorData(dataID, size, valueIndices, values);
}

void SolverInterface:: readVectorData
(
  int     dataID,
  int     valueIndex,
  double* value )
{
  return _impl->readVectorData ( dataID, valueIndex, value );
}

void SolverInterface:: readScalarData
(
  int     dataID,
  int     valueIndex,
  double& value )
{
  return _impl->readScalarData ( dataID, valueIndex, value );
}

//void SolverInterface:: setExportLocation
//(
//  const std::string& location,
//  int                exportType )
//{
//  _impl->setExportLocation ( location, exportType );
//}

void SolverInterface:: exportMesh
(
  const std::string& filenameSuffix,
  int                exportType )
{
  _impl->exportMesh ( filenameSuffix, exportType );
}

void SolverInterface:: integrateScalarData
(
  int     dataID,
  double& integratedValue )
{
  _impl->integrateData ( dataID, integratedValue );
}

void SolverInterface:: integrateVectorData
(
  int     dataID,
  double* integratedValue )
{
  _impl->integrateData ( dataID, integratedValue );
}

MeshHandle SolverInterface:: getMeshHandle
(
  const std::string & meshName )
{
  return _impl->getMeshHandle ( meshName );
}

} // namespace precice

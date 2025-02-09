#pragma once

#ifdef USE_WMO_MODELS

#include "WMO_Headers.h"
#include "WMOGroup_Headers.h"

#include "WMOGroup_Part_CollisionNode.h"

const DBC_LiquidTypeRecord* WMOGroupResolveLiquidType(const CDBCStorage* DBCStorage, const SWMO_MOHD& WMOHeader, const SWMOGroup_MOGP& WMOGroupHeader);

// Fix MOCV for 3.3.5a
void WMOGroupFixColors(const SWMOGroup_MOGP& WMOGroupHeader, CBgra* mocv, uint32 mocv_count, const SWMOGroup_MOBA* WMOGroupBatchDefinitions);

void WMOGroupFixColors_2(const SWMO_MOHD& WMOHeader, const SWMOGroup_MOGP& WMOGroupHeader, CBgra* mocv, uint32 mocv_count, const SWMOGroup_MOBA* moba);

void TraverseBsp(const std::vector<std::shared_ptr<CWMOGroup_Part_CollisionNode>>& CollisionNodes, int16 CollisionNodeIndex, BoundingBox Eyes, BoundingBox Box, std::function<void(std::shared_ptr<CWMOGroup_Part_CollisionNode>)> Action);


#endif
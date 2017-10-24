//*****************************************************************//
//    Albany 2.0:  Copyright 2012 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#include "PHAL_AlbanyTraits.hpp"

#include "FELIX_HydrologyResidualThicknessEqn.hpp"
#include "FELIX_HydrologyResidualThicknessEqn_Def.hpp"

PHAL_INSTANTIATE_TEMPLATE_CLASS_WITH_EXTRA_ARGS(FELIX::HydrologyResidualThicknessEqn,true,false)
PHAL_INSTANTIATE_TEMPLATE_CLASS_WITH_EXTRA_ARGS(FELIX::HydrologyResidualThicknessEqn,true,true)
PHAL_INSTANTIATE_TEMPLATE_CLASS_WITH_EXTRA_ARGS(FELIX::HydrologyResidualThicknessEqn,false,false)
PHAL_INSTANTIATE_TEMPLATE_CLASS_WITH_EXTRA_ARGS(FELIX::HydrologyResidualThicknessEqn,false,true)

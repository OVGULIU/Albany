//*****************************************************************//
//    Albany 2.0:  Copyright 2012 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#ifndef FELIX_HYDROLOGY_RESIDUAL_EVOLUTION_EQN_H_HPP
#define FELIX_HYDROLOGY_RESIDUAL_EVOLUTION_EQN_H_HPP 1

#include "Phalanx_config.hpp"
#include "Phalanx_Evaluator_WithBaseImpl.hpp"
#include "Phalanx_Evaluator_Derived.hpp"
#include "Phalanx_MDField.hpp"
#include "Albany_Layouts.hpp"

namespace FELIX
{

/** \brief Hydrology Mass Equation Residual Evaluator

    This evaluator evaluates the residual of the Hydrology model
*/

template<typename EvalT, typename Traits, bool IsStokes>
class HydrologyResidualThicknessEqn : public PHX::EvaluatorWithBaseImpl<Traits>,
                                      public PHX::EvaluatorDerived<EvalT, Traits>
{
public:

  typedef typename EvalT::ScalarT         ScalarT;
  typedef typename EvalT::MeshScalarT     MeshScalarT;
  typedef typename EvalT::ParamScalarT    ParamScalarT;

  typedef typename std::conditional<IsStokes,ScalarT,ParamScalarT>::type     IceScalarT;

  HydrologyResidualThicknessEqn (const Teuchos::ParameterList& p,
                                 const Teuchos::RCP<Albany::Layouts>& dl);

  void postRegistrationSetup (typename Traits::SetupData d,
                              PHX::FieldManager<Traits>& fm);

  void evaluateFields(typename Traits::EvalData d);

private:

  // Input:
  PHX::MDField<const RealType>      BF;
  PHX::MDField<const MeshScalarT>   w_measure;
  PHX::MDField<const ScalarT>       h;
  PHX::MDField<const ScalarT>       h_dot;
  PHX::MDField<const ScalarT>       N;
  PHX::MDField<const ScalarT>       m;
  PHX::MDField<const IceScalarT>    u_b;

  // Output:
  PHX::MDField<ScalarT>             residual;

  int numNodes;
  int numQPs;

  double use_eff_cav;
  double rho_i_inv;
  double h_r;
  double l_r;
  double A;
  double scaling_h_t;

  bool unsteady;
  bool nodal_equation;

  // Variables necessary for stokes coupling
  bool                            stokes_coupling;
  std::string                     sideSetName;
  std::vector<std::vector<int> >  sideNodes;
};

} // Namespace FELIX

#endif // FELIX_HYDROLOGY_RESIDUAL_EVOLUTION_EQN_H_HPP

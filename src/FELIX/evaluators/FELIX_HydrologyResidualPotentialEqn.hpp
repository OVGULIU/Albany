//*****************************************************************//
//    Albany 2.0:  Copyright 2012 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#ifndef FELIX_HYDROLOGY_RESIDUAL_ELLIPTIC_EQN_HPP
#define FELIX_HYDROLOGY_RESIDUAL_ELLIPTIC_EQN_HPP 1

#include "Phalanx_config.hpp"
#include "Phalanx_Evaluator_WithBaseImpl.hpp"
#include "Phalanx_Evaluator_Derived.hpp"
#include "Phalanx_MDField.hpp"
#include "Albany_Layouts.hpp"

namespace FELIX
{

/** \brief Hydrology ResidualPotentialEqn Evaluator

    This evaluator evaluates the residual of the Hydrology model (quasi-static formulation)
*/

template<typename EvalT, typename Traits, bool HasThicknessEqn, bool IsStokesCoupling>
class HydrologyResidualPotentialEqn : public PHX::EvaluatorWithBaseImpl<Traits>,
                                      public PHX::EvaluatorDerived<EvalT, Traits>
{
public:

  typedef typename EvalT::MeshScalarT   MeshScalarT;
  typedef typename EvalT::ParamScalarT  ParamScalarT;
  typedef typename EvalT::ScalarT       ScalarT;

  typedef typename std::conditional<IsStokesCoupling,ScalarT,ParamScalarT>::type  uScalarT;
  typedef typename std::conditional<HasThicknessEqn,ScalarT,ParamScalarT>::type   hScalarT;

  HydrologyResidualPotentialEqn (const Teuchos::ParameterList& p,
                                 const Teuchos::RCP<Albany::Layouts>& dl);

  void postRegistrationSetup (typename Traits::SetupData d,
                              PHX::FieldManager<Traits>& fm);

  void evaluateFields (typename Traits::EvalData d);

private:

  // Input:
  PHX::MDField<const RealType>      BF;
  PHX::MDField<const RealType>      GradBF;
  PHX::MDField<const MeshScalarT>   w_measure;
  PHX::MDField<const ScalarT>       N;
  PHX::MDField<const ScalarT>       N_nodal;
  PHX::MDField<const ScalarT>       q;
  PHX::MDField<const hScalarT>      h;
  PHX::MDField<const hScalarT>      h_nodal;
  PHX::MDField<const ScalarT>       m;
  PHX::MDField<const ScalarT>       m_nodal;
  PHX::MDField<const ParamScalarT>  omega;
  PHX::MDField<const uScalarT>      u_b;

  // Input only needed if equation is on a sideset
  PHX::MDField<const MeshScalarT,Cell,Side,QuadPoint,Dim,Dim>   metric;

  // Output:
  PHX::MDField<ScalarT>       residual;

  int numNodes;
  int numQPs;
  int numDims;

  double eta_i;
  double use_eff_cav;
  double mu_w;
  double rho_combo;
  double h_r;
  double l_r;
  double A;
  double scaling_omega;
  double scaling_q;

  bool mass_lumping;

  // Variables necessary for stokes coupling
  std::string                     sideSetName;
  std::vector<std::vector<int> >  sideNodes;
};

} // Namespace FELIX

#endif // FELIX_HYDROLOGY_RESIDUAL_ELLIPTIC_EQN_HPP

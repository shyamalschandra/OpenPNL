/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                INTEL CORPORATION PROPRIETARY INFORMATION                //
//   This software is supplied under the terms of a license agreement or   //
//  nondisclosure agreement with Intel Corporation and may not be copied   //
//   or disclosed except in accordance with the terms of that agreement.   //
//       Copyright (c) 2003 Intel Corporation. All Rights Reserved.        //
//                                                                         //
//  File:      pnlCondSoftMaxDistribFun.hpp                                //
//                                                                         //
//  Purpose:   CCondSoftMaxDistribFun class definition                     //
//                                                                         //
//  Author(s): (in alphabetical order)                                     //
//             Abrosimova, Bader, Chernishova, Gergel, Senin, Sidorov,     //
//             Sysoyev, Vinogradov                                         //
//             NNSU                                                        //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __PNLCONDSOFTMAXDISTRIBFUN_HPP__
#define __PNLCONDSOFTMAXDISTRIBFUN_HPP__

#include "pnlDistribFun.hpp"
#include "pnlSoftMaxDistribFun.hpp"
//#include "pnl2DNumericDenseMatrix.hpp"
//#include "pnl2DMatrix.hpp"

PNL_BEGIN

template <class Type> class C2DNumericDenseMatrix;
class CSoftMaxDistribFun;

class CCondSoftMaxDistribFun : public CDistribFun
{
public:
  static CCondSoftMaxDistribFun* Create(int nNodes,
    const CNodeType *const* nodeTypes,
    CSoftMaxDistribFun* const pDefaultDistr = NULL);

  virtual void CreateDefaultMatrices(int typeOfMatrices = 1);

  CDistribFun& operator=(const CDistribFun& pInputDistr);

  virtual CDistribFun* Clone() const;

  virtual CDistribFun* CloneWithSharedMatrices();

  virtual void AllocMatrix(const float *data, EMatrixType mType, 
    int numberOfWeightMatrix = -1, const int *parentIndices = NULL);

  virtual void AllocOffsetVector(const float *data, const int *parentIndices);

  virtual void AttachMatrix(CMatrix<float> *pMatrix, EMatrixType mType,
    int numberOfWeightMatrix = -1, const int *parentIndices = NULL,
    bool isMultipliedByDelta = 0);

  virtual void AttachOffsetVector(const floatVector *pVector, 
    const int *parentIndices);

  static CCondSoftMaxDistribFun* Copy(const CCondSoftMaxDistribFun* pInpDistr);

  void SetDistribFun(CSoftMaxDistribFun* inputDistr, 
    const int* discreteParentCombination);

  //we can create distribution functions without asking about their contens
  //and alloc or attach matrices after that
  void AllocDistribFun(const int* discreteParentCombination, 
    int isUniform = 0);

  const CSoftMaxDistribFun* GetDistribution(const int* discrParentIndex) const;

  virtual bool IsValid(std::string* descriptionOut = NULL) const;

  inline int IsDistributionSpecific() const;
  //if 0 - full distribution (non delta, non uniform, non mixed, can haven't valid form - use GetFlagMoment, GetFlagCanonical)
  //if 1 - uniform distribution - have no matrices, only size

  int GetMultipliedDelta(const int **positions, const float **values, 
    const int **offsets) const;

  CDistribFun *ConvertCPDDistribFunToPot() const;

  CDistribFun *CPD_to_pi(CDistribFun *const* allPiMessages, 
    int *multParentIndices, int numMultNodes, int posOfExceptParent = -1, 
    int maximizeFlag = 0) const;

  CDistribFun *CPD_to_lambda(const CDistribFun *lambda, 
    CDistribFun *const* allPiMessages, int *multParentIndices,
    int numMultNodes, int posOfExceptNode = -1, int maximizeFlag = 0) const;

  virtual void  MarginalizeData(const CDistribFun* pOldData, 
    const int *DimOfKeep, int NumDimsOfKeep, int maximize);

  void ShrinkObservedNodes(const CDistribFun* pOldData,
    const int *pVarsObserved, const Value* const* pObsValues, int numObsVars,
    const CNodeType* pObsTabNT, const CNodeType* pObsGauNT);

  void ExpandData(const int* pDimsToExtend, 
    int numDimsToExpand, const Value* const* valuesArray, 
    const CNodeType* const*allFullNodeTypes, int UpdateCanonical = 1);

  virtual void MultiplyInSelfData(const int *pBigDomain, 
    const int *pSmallDomain, const CDistribFun *pOtherData);

  virtual void SumInSelfData(const int *pBigDomain, 
    const int *pSmallDomain, const CDistribFun *pOtherData);

  virtual void DivideInSelfData(const int *pBigDomain, 
    const int *pSmallDomain, const CDistribFun *pOtherData);

  virtual CMatrix<float> *GetMatrix(EMatrixType mType, 
    int numWeightMat = -1,
    const int *parentIndices = NULL) const;

  floatVector *GetOffsetVector(const int *parentIndices) const;

  virtual CMatrix<float> *GetStatisticalMatrix(EStatisticalMatrix mType, 
    int *parentIndices = NULL) const;

  floatVector *GetStatisticalOffsetVector(int *parentIndices) const;

  void InitLearnData();

  void CopyLearnDataToDistrib();

  virtual void SetStatistics(const CMatrix<float> *pMat, 
    EStatisticalMatrix matrix, const int* parentsComb = NULL);

  void SetOffsetStatistics(const floatVector *pVec, const int* parentsComb);

  virtual void UpdateStatisticsEM(const CDistribFun* infData, 
    const CEvidence *pEvidence = NULL, float weightingCoeff = 1.0f,
    const int* domain = NULL);

  virtual void UpdateStatisticsML(const CEvidence* const* pEvidences, 
    int EvidenceNumber, const int *domain, float weightingCoeff = 1.0f);

  virtual void ClearStatisticalData();

  float ProcessingStatisticalData(float numEvidences);

  virtual int IsEqual(const CDistribFun *dataToCompare, float epsilon,
    int withCoeff = 1, float* maxDifferenceOut = NULL) const;

  virtual CDistribFun* GetNormalized() const;

  virtual void Normalize();

  virtual CNodeValues* GetMPE() ;

  virtual CDistribFun* ConvertToSparse() const;

  virtual CDistribFun* ConvertToDense() const;

  virtual int IsSparse() const;

  virtual int IsDense() const;

  virtual void Dump() const;

  virtual int GetNumberOfFreeParameters() const;

  CCondSoftMaxDistribFun::~CCondSoftMaxDistribFun();

  void SetMaximizingMethod(EMaximizingMethod met);

  EMaximizingMethod GetMaximizingMethod();

  void MaximumLikelihood(float **Observation, int NumberOfObservations, 
    float Accuracy, float step = 0.1);

protected:
  CCondSoftMaxDistribFun(int nNodes, const CNodeType *const* nodeTypes,
    CSoftMaxDistribFun* const pDefaultDistr);

  CCondSoftMaxDistribFun(const CCondSoftMaxDistribFun & inpDistr);

  CCondSoftMaxDistribFun(int nNodes, const CNodeType* const* pNodeTypes,
    CMatrix<CSoftMaxDistribFun*> const* pDistribMatrix);

private:
  //we divide parents to discrete & continuous 
  //- corresponding indices keep here
  intVector m_contParentsIndex;
  intVector m_discrParentsIndex;

  EMaximizingMethod m_MaximizingMethod;
  // defines method, which is used for Maximizing Likelihood

  CMatrix<CSoftMaxDistribFun*>* m_distribution;
  // this matrix contain pointers
  // to SoftMaxDistribFun on Tabular child & Gaussian parents
  // which corresponds discrete parent combination
  // order of discrete parents in such matrix corresponds such order in nodeTypes
  // and domain (for corresponding factor)

  int m_numOfDiscreteParConfs; 
  // number of configurations of states of discrete parents
  // number of weight matrixes and offset vectors is equal 
  // to number of configurations
};

inline int CCondSoftMaxDistribFun::IsDistributionSpecific() const
{
  if (m_bUnitFunctionDistribution)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

PNL_END

#endif //__PNLGAUSSIANDISTRIBFUN_HPP__
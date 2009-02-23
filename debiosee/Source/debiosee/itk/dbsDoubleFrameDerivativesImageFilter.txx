// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-23

#ifndef _dbsDoubleFrameDerivativesImageFilter_txx
#define _dbsDoubleFrameDerivativesImageFilter_txx

#include "dbsDoubleFrameDerivativesImageFilter.h"
#include "itkExceptionObject.h"

#include "itkWeightedAddImageFilter.h"
#include "itkDerivativeImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"

#include "vnl/vnl_math.h"

namespace debiosee
{

/*
 * Constructor
 */
template<class TInputImage, class TOutputImage> DoubleFrameDerivativesImageFilter<
		TInputImage, TOutputImage>::DoubleFrameDerivativesImageFilter()
{
	m_SecondDerivative = false;

	this->SetNumberOfRequiredInputs(2);

	this->SetNumberOfRequiredOutputs(3);
	OutputImagePointer outputPtrX = OutputImageType::New();
	this->SetNthOutput(0, outputPtrX.GetPointer());
	OutputImagePointer outputPtrY = OutputImageType::New();
	this->SetNthOutput(1, outputPtrY.GetPointer());
	OutputImagePointer outputPtrT = OutputImageType::New();
	this->SetNthOutput(2, outputPtrT.GetPointer());
}

template<class TInputImage, class TOutputImage> void DoubleFrameDerivativesImageFilter<
		TInputImage, TOutputImage>::SetSecondDerivative(bool d2)
{
	m_SecondDerivative = d2;

	if(d2 == true)
	{
		this->SetNumberOfRequiredOutputs(8);
		OutputImagePointer outputPtrXX = OutputImageType::New();
		this->SetNthOutput(3, outputPtrXX.GetPointer());
		OutputImagePointer outputPtrYY = OutputImageType::New();
		this->SetNthOutput(4, outputPtrYY.GetPointer());
		OutputImagePointer outputPtrXY = OutputImageType::New();
		this->SetNthOutput(5, outputPtrXY.GetPointer());
		OutputImagePointer outputPtrXT = OutputImageType::New();
		this->SetNthOutput(6, outputPtrXT.GetPointer());
		OutputImagePointer outputPtrYT = OutputImageType::New();
		this->SetNthOutput(7, outputPtrYT.GetPointer());
	}
	else
	{
		this->SetNthOutput(3, NULL);
		this->SetNthOutput(4, NULL);
		this->SetNthOutput(5, NULL);
		this->SetNthOutput(6, NULL);
		this->SetNthOutput(7, NULL);
		this->SetNumberOfRequiredOutputs(3);
	}
}

/*
 * GenerateData for non downward divisible schedules
 */
template<class TInputImage, class TOutputImage> void DoubleFrameDerivativesImageFilter<
		TInputImage, TOutputImage>::GenerateData()
{

	// Get the input and output pointers
	InputImageConstPointer inputPtr1 = this->GetInput(0);
	InputImageConstPointer inputPtr2 = this->GetInput(1);
	OutputImagePointer outputPtrX = this->GetOutput(0);
	OutputImagePointer outputPtrY = this->GetOutput(1);
	OutputImagePointer outputPtrT = this->GetOutput(2);

	// The spatial derivative is calculated on the average of the double-frames.
	typedef itk::WeightedAddImageFilter< InputImageType, InputImageType, OutputImageType > AverageType;
	typename AverageType::Pointer spatialAverage = AverageType::New();
	spatialAverage->SetInput1(inputPtr1);
	spatialAverage->SetInput2(inputPtr2);
	spatialAverage->SetAlpha(0.5);

	// Calculate the spatial derivate.
	typedef itk::DerivativeImageFilter< InputImageType, InputImageType > DerivativeType;
	// dx
	typename DerivativeType::Pointer derivativeX = DerivativeType::New();
	derivativeX->SetInput(spatialAverage->GetOutput());
	derivativeX->SetOrder(1);
	derivativeX->SetDirection(0);
	derivativeX->GraftOutput(outputPtrX);
	derivativeX->Update();
	this->GraftNthOutput(0, derivativeX->GetOutput());
	// dy
	typename DerivativeType::Pointer derivativeY = DerivativeType::New();
	derivativeY->SetInput(spatialAverage->GetOutput());
	derivativeY->SetOrder(1);
	derivativeY->SetDirection(1);
	derivativeY->GraftOutput(outputPtrY);
	derivativeY->Update();
	this->GraftNthOutput(1, derivativeY->GetOutput());

	// The temporal derivate is simply equivalent of
	// the difference between images followed by Gaussian smoothing.
	// dt
	typedef itk::SubtractImageFilter< InputImageType, InputImageType, OutputImageType >
			SubtractType;
	typename SubtractType::Pointer subtract = SubtractType::New();
	subtract->SetInput(0, inputPtr2);
	subtract->SetInput(1, inputPtr1);
	subtract->GraftOutput(outputPtrT);
	subtract->Update();
	this->GraftNthOutput(2, subtract->GetOutput());
/*	typedef itk::SmoothingRecursiveGaussianImageFilter< OutputImageType, OutputImageType > SmoothingType;
	typename SmoothingType::Pointer smoother = SmoothingType::New();
	smoother->SetInput(subtract->GetOutput());
	smoother->GraftOutput(outputPtrT);
	smoother->Update();
	this->GraftNthOutput(2, smoother->GetOutput());
*/
	if(this->GetSecondDerivative())
	{
		OutputImagePointer outputPtrXX = this->GetOutput(3);
		OutputImagePointer outputPtrYY = this->GetOutput(4);
		OutputImagePointer outputPtrXY = this->GetOutput(5);
		OutputImagePointer outputPtrXT = this->GetOutput(6);
		OutputImagePointer outputPtrYT = this->GetOutput(7);
		// dxdx
		typename DerivativeType::Pointer derivativeXX = DerivativeType::New();
		derivativeXX->SetInput(spatialAverage->GetOutput());
		derivativeXX->SetOrder(2);
		derivativeXX->SetDirection(0);
		derivativeXX->GraftOutput(outputPtrXX);
		derivativeXX->Update();
		this->GraftNthOutput(3, derivativeXX->GetOutput());
		// dydy
		typename DerivativeType::Pointer derivativeYY = DerivativeType::New();
		derivativeYY->SetInput(spatialAverage->GetOutput());
		derivativeYY->SetOrder(2);
		derivativeYY->SetDirection(1);
		derivativeYY->GraftOutput(outputPtrYY);
		derivativeYY->Update();
		this->GraftNthOutput(4, derivativeYY->GetOutput());
		// dxdy
		typename DerivativeType::Pointer derivativeXY = DerivativeType::New();
		derivativeXY->SetInput(derivativeY->GetOutput());
		derivativeXY->SetOrder(1);
		derivativeXY->SetDirection(0);
		derivativeXY->GraftOutput(outputPtrXY);
		derivativeXY->Update();
		this->GraftNthOutput(5, derivativeXY->GetOutput());
		// dxdt
		typename DerivativeType::Pointer derivativeXT = DerivativeType::New();
		derivativeXT->SetInput(subtract->GetOutput());
		derivativeXT->SetOrder(1);
		derivativeXT->SetDirection(0);
		derivativeXT->GraftOutput(outputPtrXT);
		derivativeXT->Update();
		this->GraftNthOutput(6, derivativeXT->GetOutput());
		// dydt
		typename DerivativeType::Pointer derivativeYT = DerivativeType::New();
		derivativeYT->SetInput(subtract->GetOutput());
		derivativeYT->SetOrder(1);
		derivativeYT->SetDirection(1);
		derivativeYT->GraftOutput(outputPtrYT);
		derivativeYT->Update();
		this->GraftNthOutput(7, derivativeYT->GetOutput());
	}
}

/*
 * PrintSelf method
 */
template<class TInputImage, class TOutputImage> void DoubleFrameDerivativesImageFilter<
		TInputImage, TOutputImage>::PrintSelf(std::ostream& os, Indent indent) const
{
	Superclass::PrintSelf(os, indent);
}

} // namespace dbs

#endif

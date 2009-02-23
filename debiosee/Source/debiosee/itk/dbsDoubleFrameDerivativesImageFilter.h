// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-23

#ifndef __dbsDoubleFrameDerivativesImageFilter_h
#define __dbsDoubleFrameDerivativesImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkArray2D.h"

using namespace itk;

namespace debiosee
{

/** \class DoubleFrameDerivativesImageFilter
 */
template<class TInputImage, class TOutputImage> class ITK_EXPORT DoubleFrameDerivativesImageFilter :
	public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
	/** Standard class typedefs. */
	typedef DoubleFrameDerivativesImageFilter Self;
	typedef ImageToImageFilter<TInputImage,TOutputImage> Superclass;
	typedef SmartPointer<Self> Pointer;
	typedef SmartPointer<const Self> ConstPointer;

	/** Method for creation through the object factory. */
	itkNewMacro(Self);

	/** Run-time type information (and related methods). */
	itkTypeMacro(DoubleFrameDerivativesImageFilter, ImageToImageFilter);

	/** ImageDimension enumeration. */
	itkStaticConstMacro(ImageDimension, unsigned int,
			TInputImage::ImageDimension);
	itkStaticConstMacro(OutputImageDimension, unsigned int,
			TOutputImage::ImageDimension);

	/** Inherit types from Superclass. */
	typedef typename Superclass::InputImageType InputImageType;
	typedef typename Superclass::OutputImageType OutputImageType;
	typedef typename Superclass::InputImagePointer InputImagePointer;
	typedef typename Superclass::OutputImagePointer OutputImagePointer;
	typedef typename Superclass::InputImageConstPointer InputImageConstPointer;

	void SetInput1( InputImageType * image) { this->SetNthInput(0, image); };
	void SetInput2( InputImageType * image) { this->SetNthInput(1, image); };

	void SetSecondDerivative(bool d2);
	void SecondDerivativeOn() {SetSecondDerivative(true);};
	void SecondDerivativeOff() {SetSecondDerivative(false);};
	itkGetMacro(SecondDerivative, bool);

protected:
	DoubleFrameDerivativesImageFilter();
	~DoubleFrameDerivativesImageFilter()
	{
	}
	;
	void PrintSelf(std::ostream&os, Indent indent) const;

	/** Generate the output data. */
	void GenerateData();

	bool m_SecondDerivative;


private:
	DoubleFrameDerivativesImageFilter(const Self&); //purposely not implemented
	void operator=(const Self&); //purposely not implemented

};

} // namespace dbs

#ifndef ITK_MANUAL_INSTANTIATION
#include "dbsDoubleFrameDerivativesImageFilter.txx"
#endif

#endif

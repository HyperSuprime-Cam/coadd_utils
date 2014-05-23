// -*- LSST-C++ -*-

/* 
 * LSST Data Management System
 * Copyright 2008, 2009, 2010 LSST Corporation.
 * 
 * This product includes software developed by the
 * LSST Project (http://www.lsst.org/).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the LSST License Statement and 
 * the GNU General Public License along with this program.  If not, 
 * see <http://www.lsstcorp.org/LegalNotices/>.
 */
 
/**
* @file
*
* @author Russell Owen
*/
#include "boost/format.hpp"

#include "lsst/pex/exceptions.h"
#include "lsst/coadd/utils/setCoaddEdgeBits.h"

namespace pexExcept = lsst::pex::exceptions;
namespace afwImage = lsst::afw::image;
namespace coaddUtils = lsst::coadd::utils;

template<typename WeightPixelT>
void coaddUtils::setCoaddEdgeBits(
    // spell out lsst:afw::image to make Doxygen happy
    lsst::afw::image::Mask<lsst::afw::image::MaskPixel> &coaddMask,
    lsst::afw::image::Image<WeightPixelT> const &weightMap
) {
    typedef afwImage::Mask<afwImage::MaskPixel>::x_iterator MaskXIter;
    typedef typename afwImage::Image<WeightPixelT>::const_x_iterator WeightMapConstXIter;

    if (coaddMask.getDimensions() != weightMap.getDimensions()) {
        throw LSST_EXCEPT(pexExcept::InvalidParameterException,
            (boost::format("coaddMask and weightMap dimensions differ: %dx%d != %dx%d") %
            coaddMask.getWidth() % coaddMask.getHeight() % weightMap.getWidth() % weightMap.getHeight()
            ).str());
    }
    
    afwImage::MaskPixel const edgeMask = afwImage::Mask<afwImage::MaskPixel>::getPlaneBitMask("NO_DATA");

    // Set the pixels row by row, to avoid repeated checks for end-of-row
    for (int y = 0, endY = weightMap.getHeight(); y != endY; ++y) {
        WeightMapConstXIter weightMapPtr = weightMap.row_begin(y);
        WeightMapConstXIter const weightMapEndPtr = weightMap.row_end(y);
        MaskXIter coaddMaskPtr = coaddMask.row_begin(y);
        for (; weightMapPtr != weightMapEndPtr; ++weightMapPtr, ++coaddMaskPtr) {
            if (*weightMapPtr == 0) {
                (*coaddMaskPtr) = (*coaddMaskPtr) | edgeMask;
            }
        }
    }
}

//
// Explicit instantiations
//
/// \cond
#define INSTANTIATE(WEIGHTPIXEL) \
    template void coaddUtils::setCoaddEdgeBits<WEIGHTPIXEL>( \
        afwImage::Mask<afwImage::MaskPixel> &coaddMask, \
        afwImage::Image<WEIGHTPIXEL> const &weightMap \
    );

INSTANTIATE(double);
INSTANTIATE(float);
INSTANTIATE(int);
INSTANTIATE(boost::uint16_t);
/// \endcond

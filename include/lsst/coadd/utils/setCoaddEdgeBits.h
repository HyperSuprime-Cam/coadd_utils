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
 
#ifndef LSST_COADD_UTILS_SETCOADDEDGEBITS_H
#define LSST_COADD_UTILS_SETCOADDEDGEBITS_H
/**
* @file
*
* @author Russell Owen
*/
#include "boost/cstdint.hpp"

#include "lsst/afw/image.h"

namespace lsst {
namespace coadd {
namespace utils {
    
    /**
    * @brief set edge bits of coadd mask based on weight map
    *
    * Set pixels in the image to the edge pixel when the corresponding pixel in the weight map is zero.
    * The edge pixel is image=nan, variance=inf, mask=NO_DATA for masked images and image=nan for plain images.
    *
    * @throw pexExcept::InvalidParameterException if the dimensions of coaddMask and weightMap do not match.
    */
    template<typename WeightPixelT>
    void setCoaddEdgeBits(
        lsst::afw::image::Mask<lsst::afw::image::MaskPixel> &coaddMask, ///< [in,out] mask of coadd
        lsst::afw::image::Image<WeightPixelT> const &weightMap          ///< weight map
    );

}}} // lsst::coadd::utils

#endif // !defined(LSST_COADD_UTILS_SETCOADDEDGEBITS_H)

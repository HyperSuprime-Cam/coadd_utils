// -*- lsst-c++ -*-

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
 
%define utilsLib_DOCSTRING
"
Python interface to lsst::coadd::utils functions and classes
"
%enddef

%feature("autodoc", "1");
%module(package="lsst.coadd.utils", docstring=utilsLib_DOCSTRING) utilsLib

// Everything we will need in the _wrap.cc file
%{
#include "boost/cstdint.hpp"
#include "lsst/pex/logging.h"
#include "lsst/afw/cameraGeom.h"
#include "lsst/afw/geom/polygon.h"
#include "lsst/coadd/utils.h"
%}

%include "lsst/p_lsstSwig.i"
%import "lsst/afw/image/imageLib.i"

%lsst_exceptions()

%include "lsst/coadd/utils/copyGoodPixels.h"
%define %COPYGOODPIXELS(IMAGEPIXEL)
    %template(copyGoodPixels) lsst::coadd::utils::copyGoodPixels<IMAGEPIXEL>;
%enddef
%COPYGOODPIXELS(double);
%COPYGOODPIXELS(float);
%COPYGOODPIXELS(int);
%COPYGOODPIXELS(boost::uint16_t);

%include "lsst/coadd/utils/addToCoadd.h"
%define %ADDTOCOADD(COADDPIXEL, WEIGHTPIXEL)
    %template(addToCoadd) lsst::coadd::utils::addToCoadd<COADDPIXEL, WEIGHTPIXEL>;
%enddef
%ADDTOCOADD(double, double);
%ADDTOCOADD(double, float);
%ADDTOCOADD(double, int);
%ADDTOCOADD(double, boost::uint16_t);
%ADDTOCOADD(float, double);
%ADDTOCOADD(float, float);
%ADDTOCOADD(float, int);
%ADDTOCOADD(float, boost::uint16_t);

%include "lsst/coadd/utils/setCoaddEdgeBits.h"
%define %SETCOADDEDGEBITS(WEIGHTPIXEL)
    %template(setCoaddEdgeBits) lsst::coadd::utils::setCoaddEdgeBits<WEIGHTPIXEL>;
%enddef
%SETCOADDEDGEBITS(double);
%SETCOADDEDGEBITS(float);
%SETCOADDEDGEBITS(int);
%SETCOADDEDGEBITS(boost::uint16_t);

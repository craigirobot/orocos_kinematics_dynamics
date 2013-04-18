/***************************************************************************
  tag: Erwin Aertbelien  Mon May 10 19:10:36 CEST 2004  rotational_interpolation.cxx

                        rotational_interpolation.cxx -  description
                           -------------------
    begin                : Mon May 10 2004
    copyright            : (C) 2012 Wouter Bancken
    					   (C) 2004 Erwin Aertbelien
    email                : erwin.aertbelien@mech.kuleuven.ac.be

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/
/*****************************************************************************
 *  \author
 *  	Erwin Aertbelien, Div. PMA, Dep. of Mech. Eng., K.U.Leuven
 *
 *  \version
 *		ORO_Geometry V0.2
 *
 *	\par History
 *		- $log$
 *
 *	\par Release
 *		$Id: rotational_interpolation.cpp,v 1.1.1.1.2.3 2003/02/24 13:13:06 psoetens Exp $
 *		$Name:  $
 ****************************************************************************/

#include "utilities/error.h"
#include "utilities/error_stack.h"
#include "rotational_interpolation.hpp"
#include "rotational_interpolation_sa.hpp"
#include <memory>
#include <cstring>

namespace KDL {

using namespace std;

typedef boost::shared_ptr<RotationalInterpolation_SingleAxis> RotationalInterpolationSingleAxisPtr;

int RotationalInterpolation::Read(istream& is, RotationalInterpolationPtr& returned_interpolation) {
	IOTrace("RotationalInterpolation::Read");
	char storage[64];
	EatWord(is,"[",storage,sizeof(storage));
	Eat(is,'[');
	int exit_code;
	if (strcmp(storage,"SINGLEAXIS")==0) {
		IOTrace("SINGLEAXIS");
		EatEnd(is,']');
		IOTracePop();
		IOTracePop();
		RotationalInterpolationSingleAxisPtr interpolation;
		exit_code = RotationalInterpolation_SingleAxis::Create(interpolation);
		if(exit_code != 0) {
			returned_interpolation = RotationalInterpolationSingleAxisPtr();
			return exit_code;
		}
		returned_interpolation = interpolation;
		return 0;
	} else if (strcmp(storage,"THREEAXIS")==0) {
		IOTrace("THREEAXIS");
		return 148;
		EatEnd(is,']');
		IOTracePop();
		IOTracePop();
		returned_interpolation = RotationalInterpolationPtr();
	} else if (strcmp(storage,"TWOAXIS")==0) {
		IOTrace("TWOAXIS");
		return 148;
		EatEnd(is,']');
		IOTracePop();
		IOTracePop();
		returned_interpolation = RotationalInterpolationPtr();
	} else {
		return 147;
	}
	returned_interpolation = RotationalInterpolationPtr(); // just to avoid the warning;
	return 0;
}

}


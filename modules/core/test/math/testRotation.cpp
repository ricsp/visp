/****************************************************************************
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2015 by Inria. All rights reserved.
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact Inria about acquiring a ViSP Professional
 * Edition License.
 *
 * See http://visp.inria.fr for more information.
 *
 * This software was developed at:
 * Inria Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 *
 * If you have questions regarding the use of this file, please contact
 * Inria at visp@inria.fr
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Description:
 * Tests transformation from various representations of rotation.
 *
 * Authors:
 * Eric Marchand
 * Fabien Spindler
 *
 *****************************************************************************/


/*!
  \file testRotation.cpp
  \brief Tests transformation within various representations of rotation.
*/


#include <visp3/core/vpMath.h>
#include <visp3/core/vpRotationMatrix.h>
#include <visp3/io/vpParseArgv.h>
#include <visp3/core/vpQuaternionVector.h>

#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <limits>

int main()
{
  try {
    vpRotationMatrix R;
    for(int i=-10;i<10;i++){
      for(int j=-10;j<10;j++){
        vpThetaUVector tu(vpMath::rad(90+i), vpMath::rad(170+j), vpMath::rad(45)) ;
        tu.buildFrom(vpRotationMatrix(tu)); //put some coherence into rotation convention

        std::cout << "Initialization " <<std::endl ;

        double theta;
        vpColVector u;
        tu.extract(theta, u);

        std::cout << "theta=" << vpMath::deg(theta) << std::endl ;
        std::cout << "u=" << u << std::endl ;

        std::cout << "From vpThetaUVector to vpRotationMatrix " << std::endl ;
        R.buildFrom(tu)  ;

        std::cout << "Matrix R" ;
        if (R.isARotationMatrix()==1) std::cout <<" is a rotation matrix " << std::endl ;
        else std::cout <<" is not a rotation matrix " << std::endl ;

        std::cout << R << std::endl ;

        std::cout << "From vpRotationMatrix to vpQuaternionVector " << std::endl ;
        vpQuaternionVector q(R);
        std::cout << q <<std::endl ;

        R.buildFrom(q);
        std::cout << "From vpQuaternionVector to vpRotationMatrix  " << std::endl ;

        std::cout << "From vpRotationMatrix to vpRxyzVector " << std::endl ;
        vpRxyzVector RxyzBuildFromR(R) ;
        std::cout <<  RxyzBuildFromR <<std::endl ;


        std::cout << "From vpRxyzVector to vpThetaUVector " << std::endl ;
        std::cout << "  use From vpRxyzVector to vpRotationMatrix " << std::endl ;
        std::cout << "  use From vpRotationMatrix to vpThetaUVector " << std::endl ;


        vpThetaUVector tuBuildFromEu ;
        tuBuildFromEu.buildFrom(R) ;

        std::cout << std::endl ;
        std::cout <<  "result : should equivalent to the first one " << std::endl ;


        double theta2;
        vpColVector u2;

        tuBuildFromEu.extract(theta2, u2);
        std::cout << "theta=" << vpMath::deg(theta2) << std::endl ;
        std::cout << "u=" << u2 << std::endl ;

        assert(vpMath::abs(theta2-theta)<std::numeric_limits<double>::epsilon()*1e10);
        assert(vpMath::abs(u[0]-u2[0])<std::numeric_limits<double>::epsilon()*1e10);
        assert(vpMath::abs(u[1]-u2[1])<std::numeric_limits<double>::epsilon()*1e10);
        assert(vpMath::abs(u[2]-u2[2])<std::numeric_limits<double>::epsilon()*1e10);
      }
      vpRzyzVector rzyz(vpMath::rad(180), vpMath::rad(120), vpMath::rad(45)) ;
      std::cout << "Initialization vpRzyzVector " <<std::endl ;
      std::cout << rzyz << std::endl ;
      std::cout << "From vpRzyzVector to vpRotationMatrix  " << std::endl ;
      R.buildFrom(rzyz) ;
      std::cout << "From vpRotationMatrix to vpRzyzVector " << std::endl ;
      vpRzyzVector rzyz_final ;
      rzyz_final.buildFrom(R) ;
      std::cout << rzyz_final << std::endl ;


      vpRzyxVector rzyx(vpMath::rad(180), vpMath::rad(120), vpMath::rad(45)) ;
      std::cout << "Initialization vpRzyxVector " <<std::endl ;
      std::cout << rzyx << std::endl ;
      std::cout << "From vpRzyxVector to vpRotationMatrix  " << std::endl ;
      R.buildFrom(rzyx) ;
      std::cout << R << std::endl ;
      std::cout << "From vpRotationMatrix to vpRzyxVector " << std::endl ;
      vpRzyxVector rzyx_final ;
      rzyx_final.buildFrom(R) ;
      std::cout << rzyx_final << std::endl ;
    }
    return 0;
  }
  catch(vpException e) {
    std::cout << "Catch an exception: " << e << std::endl;
    return 1;
  }
}
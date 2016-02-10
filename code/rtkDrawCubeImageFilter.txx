/*=========================================================================
 *
 *  Copyright RTK Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __rtkDrawCubeImageFilter_txx
#define __rtkDrawCubeImageFilter_txx

#include <iostream>
#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIterator.h>

#include "rtkHomogeneousMatrix.h"

#include "rtkMacro.h"

namespace rtk
{

template <class TInputImage, class TOutputImage, class TSpatialObject, typename TFunction>
rtk::DrawCubeImageFilter<TInputImage, TOutputImage, TSpatialObject, TFunction>
::DrawCubeImageFilter()
{

}

void DrawCubeSpatialObject::UpdateParameters
()
{
 
  //Setting axis dimensions taking into account center
  // X-Axis superior
  m_semiprincipalaxis[0] =  m_Axis[0] + m_Center[0];
  // X-Axis inferior
  m_semiprincipalaxis[1] = -m_Axis[0] + m_Center[0];
  // Y-Axis superior
  m_semiprincipalaxis[2] =  m_Axis[1] + m_Center[1];
  // Y-Axis inferior
  m_semiprincipalaxis[3] = -m_Axis[1] + m_Center[1];
  // Z-Axis superior
  m_semiprincipalaxis[4] =  m_Axis[2] + m_Center[2];
  // Z-Axis inferior
  m_semiprincipalaxis[5] = -m_Axis[2] + m_Center[2]; 
  
}

bool DrawCubeSpatialObject::IsInside(const rtk::DrawCubeSpatialObject::PointType& point) const
{ 

 

  //Set type of Figure
  //Apply rotation if necessary
  // FIXME: add rotation option
  //sqpFunctor->Rotate(cube.angle, cube.center);

  
    if(point[0]<m_semiprincipalaxis[0] && point[0]>m_semiprincipalaxis[1] &&
       point[1]<m_semiprincipalaxis[2] && point[1]>m_semiprincipalaxis[3] &&
       point[2]<m_semiprincipalaxis[4] && point[2]>m_semiprincipalaxis[5])
      return true;
    return false;

}

}// end namespace rtk

#endif

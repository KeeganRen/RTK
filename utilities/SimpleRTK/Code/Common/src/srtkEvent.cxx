/*=========================================================================
 *
 *  Copyright Insight Software Consortium & RTK Consortium
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
#include "srtkEvent.h"

#define srtkEventToStringCaseMacro(n) case srtk##n##Event: return ( os << #n << "Event" )

namespace rtk
{
namespace simple
{

std::ostream& operator<<(std::ostream& os, const EventEnum k)
{
  switch (k)
    {
    srtkEventToStringCaseMacro(Any);
    srtkEventToStringCaseMacro(Abort);
    srtkEventToStringCaseMacro(Delete);
    srtkEventToStringCaseMacro(End);
    srtkEventToStringCaseMacro(Iteration);
    srtkEventToStringCaseMacro(Progress);
    srtkEventToStringCaseMacro(Start);
    srtkEventToStringCaseMacro(User);
    }
  return os;
}

} // end namespace simple
} // end namespace rtk
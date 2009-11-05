#ifndef __CGLA_H
#define __CGLA_H

#ifndef OLD_C_HEADERS
#include <cmath>
#include <climits>
#include <cassert>
#else
#include <math.h>
#include <limits.h>
#include <assert.h>
#endif

#include <algorithm>
#include "Common/CommonDefs.h"

namespace CGLA {

	/// Useful enum that represents coordiante axes.
enum Axis {XAXIS=0,YAXIS=1,ZAXIS=2};

template <class _Tp>
inline const _Tp& s_min(const _Tp& __a, const _Tp& __b)
{
  return __b < __a ? __b : __a;
}
template <class _Tp>
inline const _Tp& s_max(const _Tp& __a, const _Tp& __b) 
{
  return  __a < __b ? __b : __a;
}


}

#endif

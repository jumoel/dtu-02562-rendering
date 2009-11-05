#ifndef __DFTABLE_H
#define __DFTABLE_H

#include <iostream>
#include "Common/CommonDefs.h"

typedef unsigned short int FixedPoint;

namespace Components
{
	class DFTable
	{
	private:

		float table[USHRT_MAX];
		float min_F, max_F, span_F;
		float max_fp;
	public:

		FixedPoint min_fix() const {return 0;}
		FixedPoint max_fix() const {return USHRT_MAX-1;}
  
		DFTable(float _min_F, float _max_F): min_F(_min_F), max_F(_max_F)
    {
      span_F = max_F-min_F;
      max_fp = float(USHRT_MAX-1);
      for(int i=0; i<USHRT_MAX; i++)
        table[i] = (max_F-min_F)*(float(i)/max_fp) + min_F;
    }
  
		FixedPoint float2fix(float x) const 
    {
#ifdef WIN32
      return FixedPoint(max(0.0f, 
														min(max_fp,
																max_fp*(x - min_F)/(span_F)+0.5f)));
#else
			return FixedPoint(std::max(0.0f, 
																 std::min(max_fp,
																					max_fp*(x - min_F)/(span_F)+0.5f)));
#endif
    }
  
		const float& fix2float(FixedPoint i) const {return table[i];}

		FixedPoint invert(FixedPoint i) const {return USHRT_MAX-i-1;}
	};
}

namespace CMP = Components;

#endif

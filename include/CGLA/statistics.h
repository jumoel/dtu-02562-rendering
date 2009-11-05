#ifndef __STATISTICS_H
#define __STATISTICS_H

#include <vector>

namespace CGLA
{
	template<class VT>
		VT mean(const std::vector<VT>& vec)
		{
			VT v(0);
			for(int i=0;i<vec.size();++i)
				v += vec[i];
			v /= vec.size();

			return v;
		}


	/** Function that computes the covariance of a set of points.
			This function returns the mean, and, upon completion, the
			final argument contains the covariance matrix.

			This template is instantiated for Vec3f, Vec2f, and Vec4f. */
			
	template<class VT, class MT>
		VT covariance(const std::vector<VT>& vec, MT& C_out);
}




#endif

#include "statistics.h"

#include "Mat2x2f.h"
#include "Mat3x3f.h"
#include "Mat4x4f.h"

using namespace std;

namespace CGLA
{
	template<class VT, class MT>
	VT covariance(const vector<VT>& vec, MT& C_out)
	{
		VT m = mean(vec);
		int n = vec.size();

		MT C;
		for(int i=0;i<n;++i)
			{
				MT B;
				VT v = vec[i]-m;
				outer_product(v,v,B);

				C += B;
			}
		C_out = C;

		return m;
	}

	template 
	Vec2f covariance<Vec2f,Mat2x2f>(const vector<Vec2f>& vec, Mat2x2f& C_out);

	template 
	Vec3f covariance<Vec3f,Mat3x3f>(const vector<Vec3f>& vec, Mat3x3f& C_out);

	template 
	Vec4f covariance<Vec4f,Mat4x4f>(const vector<Vec4f>& vec, Mat4x4f& C_out);
}

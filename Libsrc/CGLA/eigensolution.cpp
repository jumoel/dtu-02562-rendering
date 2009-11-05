#include "eigensolution.h"
#include "Mat2x2f.h"
#include "Mat3x3f.h"
#include "Mat4x4f.h"

#include <iostream>

using namespace std;

namespace CGLA
{
	namespace
	{
		// During experiments 925 iterations were observed for a hard problem
		// Ten times that should be safe.
		const int KMAX = 10000;

		// The threshold below is the smallest that seems to give reliable
		// solutions.
		const float EV_THRESH = 0.0000001;
	}

	template <class MT>
	int power_eigensolution(const MT& Ap, MT& Q, MT& L, int max_sol)
	{
		typedef typename MT::VectorType VT;
		MT A = Ap;
		int n = min(MT::get_v_dim(), max_sol);

		for(int i=0;i<n;++i)
			{
				// Seed the eigenvector estimate
				VT q(1);
				float l,l_old;

				// As long as we haven't reached the max iterations and the
				// eigenvalue has not converged, do
				int k=0;
				for(; k<2 || k<KMAX && (l-l_old > EV_THRESH * l) ; ++k)
					{
						// Multiply the eigenvector estimate onto A
						const VT z = A * q;

						// Check that we did not get the null vector.
						float z_len = z.length();
						if(z_len < EV_THRESH)
							return i;

						// Normalize to get the new eigenvector
						q = z/z_len;

						// Record the old eigenvalue estimate and get a new estimate.
						l_old = l;
						l = dot(q, A * q);
					}
				// If we hit the max iterations, we also don't trust the eigensolution
				if(k==KMAX)
					return i;
				
				// Update the solution by adding the eigenvector to Q and
				// the eigenvalue to the diagonal of L.
				Q[i] = q;
				L[i][i] = l;

				// Update A by subtracting the subspace represented by the 
				// eigensolution just found. This is called the method of 
				// deflation.
				MT B;
				outer_product(q,q,B);
				A = A - l * B;
			}
		return n;
	}

	/* There is no reason to put this template in a header file, since 
		 we will only use it on matrices defined in CGLA. Instead, we 
		 explicitly instantiate the function for the square matrices
		 of CGLA */
	template int power_eigensolution<Mat2x2f>(const Mat2x2f&,
																						Mat2x2f&,Mat2x2f&,int);
	
	template int power_eigensolution<Mat3x3f>(const Mat3x3f&,
																						Mat3x3f&,Mat3x3f&,int);
	template int power_eigensolution<Mat4x4f>(const Mat4x4f&,
																						Mat4x4f&,Mat4x4f&,int);
}


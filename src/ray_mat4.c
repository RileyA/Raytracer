#include "ray_mat4.h"
#include "ray_math.h"

quat mat4_quat(mat4* m)
{
	// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
	// article "Quaternion Calculus and Fast Animation".
	quat out;

	real trace = m->m[0][0] + m->m[1][1] + m->m[2][2];
	real root;

	if (trace > 0.0)
	{
		// |w| > 1/2, may as well choose w > 1/2
		root = sqrt(trace + 1.0f);  // 2w
		out.w = 0.5f*root;
		root = 0.5f/root;  // 1/(4w)
		out.x = (m->m[2][1] - m->m[1][2]) * root;
		out.y = (m->m[0][2] - m->m[2][0]) * root;
		out.z = (m->m[1][0] - m->m[0][1]) * root;
	}
	else
	{
		// |w| <= 1/2
		static size_t s_iNext[3] = { 1, 2, 0 };
		size_t i = 0;
		if ( m->m[1][1] > m->m[0][0] )
			i = 1;
		if ( m->m[2][2] > m->m[i][i] )
			i = 2;
		size_t j = s_iNext[i];
		size_t k = s_iNext[j];

		root = sqrt(m->m[i][i]-m->m[j][j]-m->m[k][k] + 1.0f);
		real* apkQuat[3] = { &out.x, &out.y, &out.z };
		*apkQuat[i] = 0.5f*root;
		root = 0.5f/root;
		out.w = (m->m[k][j]-m->m[j][k])*root;
		*apkQuat[j] = (m->m[j][i]+m->m[i][j])*root;
		*apkQuat[k] = (m->m[k][i]+m->m[i][k])*root;
	}

	return out;
}

void mat4_invert(mat4* m)
{
	real m00 = m->m[0][0], m01 = m->m[0][1], m02 = m->m[0][2], m03 = m->m[0][3];
	real m10 = m->m[1][0], m11 = m->m[1][1], m12 = m->m[1][2], m13 = m->m[1][3];
	real m20 = m->m[2][0], m21 = m->m[2][1], m22 = m->m[2][2], m23 = m->m[2][3];
	real m30 = m->m[3][0], m31 = m->m[3][1], m32 = m->m[3][2], m33 = m->m[3][3];

	real v0 = m20 * m31 - m21 * m30;
	real v1 = m20 * m32 - m22 * m30;
	real v2 = m20 * m33 - m23 * m30;
	real v3 = m21 * m32 - m22 * m31;
	real v4 = m21 * m33 - m23 * m31;
	real v5 = m22 * m33 - m23 * m32;

	real t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
	real t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
	real t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
	real t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

	real invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

	m->m[0][0] = t00 * invDet;
	m->m[1][0] = t10 * invDet;
	m->m[2][0] = t20 * invDet;
	m->m[3][0] = t30 * invDet;

	m->m[0][1] = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	m->m[1][1] = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	m->m[2][1] = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	m->m[3][1] = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m10 * m31 - m11 * m30;
	v1 = m10 * m32 - m12 * m30;
	v2 = m10 * m33 - m13 * m30;
	v3 = m11 * m32 - m12 * m31;
	v4 = m11 * m33 - m13 * m31;
	v5 = m12 * m33 - m13 * m32;

	m->m[0][2] = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	m->m[1][2] = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	m->m[2][2] = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	m->m[3][2] = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m21 * m10 - m20 * m11;
	v1 = m22 * m10 - m20 * m12;
	v2 = m23 * m10 - m20 * m13;
	v3 = m22 * m11 - m21 * m12;
	v4 = m23 * m11 - m21 * m13;
	v5 = m23 * m12 - m22 * m13;

	m->m[0][3] = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	m->m[1][3] = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	m->m[2][3] = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	m->m[3][3] = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;
}


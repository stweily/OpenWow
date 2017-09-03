#include "stdafx.h"

// Include

// General
#include "ModelsUtils.h"

// Additional
#include "matrix.h"

void glQuaternionRotate(cvec3 vdir, float w)
{
	Matrix m;
	Quaternion q(w, vdir);
	m.quaternionRotate(q);
	glMultMatrixf(m);
}
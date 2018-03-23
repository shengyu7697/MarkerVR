#include "RotationUtil.h"
#include "Quaternion.h"

#include <opencv2/calib3d.hpp>

using namespace cv;

// Right-Handed Coordinate Systems (same as OpenGL)
// pitch     yaw      roll
// attitude  heading  bank
// x         y        z
//
//       +y (yaw, heading)
//        │
//        |
//        └─ ─ ─ ─  +x (pitch, attitude)
//       /
//      /
//    +z (roll, bank)

// ref: http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToMatrix/index.htm
/** Euler Angles to Rotation Matrix
*   Coordinate System: right hand
*   Positive angle: right hand
*   Order of euler angles: heading first, then attitude, then bank
*   matrix row column ordering:
*   [m00 m01 m02]
*   [m10 m11 m12]
*   [m20 m21 m22]*/
Mat euler2matrix(const float &x, const float &y, const float &z) // TODO not test yet
{
	// Assuming the angles are in radians.
	float ch = cosf(y);
	float sh = sinf(y);
	float ca = cosf(x);
	float sa = sinf(x);
	float cb = cosf(z);
	float sb = sinf(z);

	float m00 = ch * ca;
	float m01 = sh*sb - ch*sa*cb;
	float m02 = ch*sa*sb + sh*cb;
	float m10 = sa;
	float m11 = ca*cb;
	float m12 = -ca*sb;
	float m20 = -sh*ca;
	float m21 = sh*sa*cb + ch*sb;
	float m22 = -sh*sa*sb + ch*cb;

	// [R] = ([Rh][Ra])[Rb]
	return (Mat_<float>(3,3) <<
			m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22);
}

// https://www.learnopencv.com/rotation-matrix-to-euler-angles/
// 但是 yaw ptich roll 順序有錯
// TODO 矩陣相乘後的加速版 -> euler2matrix()
Mat _euler2matrix(const float &x, const float &y, const float &z)
{
    // Calculate rotation about x axis
    Mat Rx = (Mat_<float>(3,3) <<
               1,       0,        0,
               0,       cos(x),  -sin(x),
               0,       sin(x),   cos(x)
               );

    // Calculate rotation about y axis
    Mat Ry = (Mat_<float>(3,3) <<
               cos(y),    0,      sin(y),
               0,         1,      0,
              -sin(y),    0,      cos(y)
               );

    // Calculate rotation about z axis
    Mat Rz = (Mat_<float>(3,3) <<
               cos(z),   -sin(z),       0,
               sin(z),    cos(z),       0,
               0,         0,            1);


    // Combined rotation matrix
    // [R] = ([Ry][Rx])[Rz]
    // heading, attitude, bank
    // yaw,     ptich,    roll
    return Ry * Rx * Rz;
}


// Calculates rotation matrix given euler angles.
Mat euler2matrix(Vec3f &theta)
{
    return _euler2matrix(theta[0], theta[1], theta[2]);
}

// ----------------------------------------------------------------------------

// Checks if a matrix is a valid rotation matrix.
static bool isRotationMatrix(const Mat &R)
{
    Mat Rt;
    transpose(R, Rt);
    Mat shouldBeIdentity = Rt * R;
    Mat I = Mat::eye(3,3, shouldBeIdentity.type());

    return norm(I, shouldBeIdentity) < 1e-6;
}

/** rotation matrix to euler angles
*   Coordinate System: right hand
*   Positive angle: right hand
*   Order of euler angles: heading first, then attitude, then bank
*   matrix row column ordering:
*   [m00 m01 m02]
*   [m10 m11 m12]
*   [m20 m21 m22]*/
Vec3f matrix2Euler(const Mat &R)
{
    assert(isRotationMatrix(R));
    float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );
    bool singular = sy < 1e-6; // If

    float x, y, z;
    if (!singular)
    {
        x = atan2(R.at<double>(2,1) , R.at<double>(2,2));
        y = atan2(-R.at<double>(2,0), sy);
        z = atan2(R.at<double>(1,0), R.at<double>(0,0));
    }
    else
    {
        x = atan2(-R.at<double>(1,2), R.at<double>(1,1));
        y = atan2(-R.at<double>(2,0), sy);
        z = 0;
    }
    return Vec3f(x, y, z);
}

// rodrigues to euler angles
void rodrigues2Euler(Vec3d &rvec, float &pitch, float &yaw, float &roll)
{
	Mat rot; // rotation matrix
	Rodrigues(rvec, rot);
	Vec3f euler = matrix2Euler(rot);
	pitch = radians2Degrees(euler[0]);
	yaw = radians2Degrees(euler[1]);
	roll = radians2Degrees(euler[2]);
}

void rodrigues2Euler(Vec3d &rvec, float euler[3])
{
	rodrigues2Euler(rvec, euler[0], euler[1], euler[2]);
}


// ----------------------------------------------------------------------------
void rodriguesRotateByEuler(Vec3d &rvec, const float &pitch, const float &yaw, const float &roll)
{
	Matx33d rot; // rotation matrix
	Rodrigues(rvec, rot);
	Vec3f e(degrees2Radians(pitch), degrees2Radians(yaw), degrees2Radians(roll));
	Matx33d m = euler2matrix(e);
	rot = rot * m; // rotate object local
	Rodrigues(rot, rvec);
}

void rodriguesRotateByEuler(Vec3d &rvec, const Vec3d &euler)
{
	rodriguesRotateByEuler(rvec, euler[0], euler[1], euler[2]);
}

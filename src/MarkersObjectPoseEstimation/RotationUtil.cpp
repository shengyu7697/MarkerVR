#include "RotationUtil.h"
#include "Quaternion.h"

#include <opencv2/calib3d.hpp>

using namespace cv;

// https://www.learnopencv.com/rotation-matrix-to-euler-angles/
// 但是 yaw ptich roll 順序有錯
// Calculates rotation matrix given euler angles.
Mat eulerAnglesToRotationMatrix(Vec3f &theta)
{
    // Calculate rotation about x axis
    Mat R_x = (Mat_<double>(3,3) <<
               1,       0,               0,
               0,       cos(theta[0]),  -sin(theta[0]),
               0,       sin(theta[0]),   cos(theta[0])
               );

    // Calculate rotation about y axis
    Mat R_y = (Mat_<double>(3,3) <<
               cos(theta[1]),    0,      sin(theta[1]),
               0,                1,      0,
              -sin(theta[1]),    0,      cos(theta[1])
               );

    // Calculate rotation about z axis
    Mat R_z = (Mat_<double>(3,3) <<
               cos(theta[2]),   -sin(theta[2]),       0,
               sin(theta[2]),    cos(theta[2]),       0,
               0,                0,                   1);


    // Combined rotation matrix
    //Mat R = R_z * R_y * R_x; // wrong
    Mat R = R_y * R_x * R_z; // yaw ptich roll

    return R;
}

// Checks if a matrix is a valid rotation matrix.
bool isRotationMatrix(Mat &R)
{
    Mat Rt;
    transpose(R, Rt);
    Mat shouldBeIdentity = Rt * R;
    Mat I = Mat::eye(3,3, shouldBeIdentity.type());

    return norm(I, shouldBeIdentity) < 1e-6;
}

// Calculates rotation matrix to euler angles
// The result is the same as MATLAB except the order
// of the euler angles ( x and z are swapped ).
Vec3f rotationMatrixToEulerAngles(Mat &R)
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

// euler angles to rotation matrix
void euler2rotm()
{
}

// rotation matrix to euler angles
void rotm2euler()
{
}

void rodriguesRotateByEulerAngles(Vec3d &rvec, const float &pitch, const float &yaw, const float &roll)
{
	Matx33d rot; // rotation matrix
	Rodrigues(rvec, rot);
	Vec3f e(degrees2Radians(pitch), degrees2Radians(yaw), degrees2Radians(roll));
	Matx33d m = eulerAnglesToRotationMatrix(e);
	rot = rot * m; // rotate object local
	Rodrigues(rot, rvec);
}

void rodriguesRotateByEulerAngles(Vec3d &rvec, const Vec3d &euler)
{
	rodriguesRotateByEulerAngles(rvec, euler[0], euler[1], euler[2]);
}

// rodrigues to euler angles
void rodrigues2Euler(Vec3d &rvec, float &pitch, float &yaw, float &roll)
{
	Mat rot; // rotation matrix
	Rodrigues(rvec, rot);
	Vec3f euler = rotationMatrixToEulerAngles(rot);
	pitch = radians2Degrees(euler[0]);
	yaw = radians2Degrees(euler[1]);
	roll = radians2Degrees(euler[2]);
}

void rodrigues2Euler(Vec3d &rvec, float euler[3])
{
	rodrigues2Euler(rvec, euler[0], euler[1], euler[2]);
}

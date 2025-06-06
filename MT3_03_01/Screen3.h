#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include <Novice.h>

struct Sphere {
	Vector3 center; // 球の中心
	float radius;   // 球の半径
};
struct Line {
	Vector3 origin; // 線の始点
	Vector3 diff;   // 線の終点
};
struct Ray {
	Vector3 origin; // 線の始点
	Vector3 diff;   // 線の終点
};
struct Segment {
	Vector3 origin; // 線の始点
	Vector3 diff;   // 線の終点
};
struct Plane {
	Vector3 normal; //!< 法線
	float distance; //!< 距離
};
struct Triangle {
	Vector3 vertices[3]; //!< 頂点
};
struct AABB {
	Vector3 min; //!< 最小点
	Vector3 max; //!< 最大点
};
struct OBB {
	Vector3 center;         //!< 中心
	Vector3 orientation[3]; //!< 軸
	Vector3 size;           //!< 半径
};


void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void DrawSegment(const Segment& segment, const Matrix4x4& wvpMatrix, const Matrix4x4& viewportMatrix, int color);
void DrawLine(const Line& line, const Matrix4x4& wvpMatrix, const Matrix4x4& viewportMatrix, int color);
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);
void DrawSphere(const Sphere& sphere, const Matrix4x4& wvpMatrix, const Matrix4x4& viewportMatrix, int color);
void DrawTriangle(const Triangle& triangle, const Matrix4x4& wvpMatrix, const Matrix4x4& viewportMatrix, int color);
void DrawAABB(const AABB& aabb, const Matrix4x4& wvpMatrix, const Matrix4x4& viewportMatrix, int color);
void DrawOBB(const OBB& obb, const Matrix4x4& wvpMatrix, const Matrix4x4& viewportMatrix, int color);	
void DrawBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2,  const Matrix4x4& wvpMatrix, const Matrix4x4& viewportMatrix, int color);

Vector3 Project(const Vector3& v1, Vector3& v2);
Vector3 ClosestPoint(const Segment& segment, const Vector3& point);
Vector3 Perpendicular(const Vector3& vector);
Vector3 Lerp(const Vector3& a, const Vector3& b, float t);



bool IsCollisionSphereToSphere(const Sphere& s1, const Sphere& s2);
bool IsCollisionSphereToPlane(const Sphere& sphere, const Plane& plane);
bool IsCollisionSegmentToPlane(const Segment& segment, const Plane& plane);
bool IsCollisionLineToPlane(const Line& line, const Plane& plane);
bool IsCollisionRayToPlane(const Ray& ray, const Plane& plane);
bool IsCollisionTriangeleToSegment(const Triangle& triangle, const Segment& segment);
bool IsCollisionAABBToAABB(const AABB& aabb1, const AABB& aabb2);
bool IsCollisionSphereToAABB(const Sphere& sphere, const AABB& aabb);
bool IsCollisionAABBtoSegment(const AABB& aabb, const Segment& segment);
bool IsCollisionAABBtoLine(const AABB& aabb, const Line& line);
bool IscoliisionOBBToSphere(const OBB& obb, const Sphere& sphere);
bool IscollisionOBBToLine(const OBB& obb, const Line& line);
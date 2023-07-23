#include <cmath>
#include <iostream>

struct Vector3
{
	float Length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector3& Normalize()
	{
		const auto length = Length();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	float Dot(const Vector3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	Vector3 Cross(const Vector3& other) const
	{
		Vector3 result;
		result.x = (y * other.z) - (z * other.y);
		result.y = (z * other.x) - (x * other.z);
		result.z = (x * other.y) - (y * other.x);
		return result;
	}

	Vector3 operator+(const Vector3& other) const
	{
		return Vector3{ *this } += other;
	}

	Vector3& operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3 operator-(const Vector3& other) const
	{
		return Vector3{ *this } -= other;
	}

	Vector3& operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3 operator*(float scalar) const
	{
		return Vector3{ *this } *= scalar;
	}

	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3 operator/(float scalar) const
	{
		return Vector3{ *this } /= scalar;
	}

	Vector3& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	Vector3 operator-() const
	{
		return Vector3{ -x, -y, -z };
	}

	float x;
	float y;
	float z;
};

int main()
{
	Vector3 p1{ 6.0f, 10.0f, -2.0f };
	Vector3 p2{ 3.0f, -1.0f, 17.0f };
	Vector3 p3{ -9.0f, 8.0f, 0.0f };

	Vector3 e1 = p3 - p2;
	Vector3 e2 = p1 - p3;
	Vector3 e3 = p2 - p1;

	Vector3 n = e2.Cross(e3).Normalize();
	float d = n.Dot(p1);

	// 4.a) plane equation:
	// n [x = 0.0497629, y = -0.867741, z = -0.494519], d = -7.38979
	{
		std::cout << "4.a)\tn [x = " << n.x << ", y = " << n.y << ", z = " << n.z << "], d = " << d << std::endl << std::endl;
	}

	// 4.b)
	// The point is in front of the triangle at a distance 1.59552
	{
		Vector3 q{ 3.0f, 4.0f, 5.0f };
		float distance = n.Dot(q) - d;
		std::cout << "4.b)\tThe point is " << (distance < 0.0f ? "behind" : "in front of") << " the triangle at a distance " << distance << std::endl << std::endl;
	}

	// 4.c)
	// Barycentric coordinates b1 = 0.641037, b2 = 1.08202, b3 = -0.723055
	{
		Vector3 q{ 13.60f, -0.46f, 17.11f };
		Vector3 d1 = q - p1;
		Vector3 d2 = q - p2;
		Vector3 d3 = q - p3;

		const auto area = e1.Cross(e2).Dot(n) / 2.0f;
		const auto area1 = e1.Cross(d3).Dot(n) / 2.0f;
		const auto area2 = e2.Cross(d1).Dot(n) / 2.0f;
		const auto area3 = e3.Cross(d2).Dot(n) / 2.0f;

		const auto b1 = area1 / area;
		const auto b2 = area2 / area;
		const auto b3 = area3 / area;

		std::cout << "4.c)\tBarycentric coordinates b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << std::endl << std::endl;
	}

	// 4.d)
	// Center of gravity: x = 0, y = 5.66667, z = 5
	{
		Vector3 c = (p1 + p2 + p3) / 3.0f;

		std::cout << "4.d)\tCenter of gravity: x = " << c.x << ", y = " << c.y << ", z = " << c.z << std::endl << std::endl;
	}

	// 4.e)
	// Incenter: x = -0.292943, y = 6.46848, z = 3.56357
	{
		auto l1 = e1.Length();
		auto l2 = e2.Length();
		auto l3 = e3.Length();
		auto p = l1 + l2 + l3;

		Vector3 ic = (p1 * l1 + p2 * l2 + p3 * l3) / p;

		std::cout << "4.e)\tIncenter: x = " << ic.x << ", y = " << ic.y << ", z = " << ic.z << std::endl << std::endl;
	}

	// 4.f)
	// Circumcenter: x = 0.135435, y = 4.6071, z = 6.87286
	{
		auto d1 = -e2.Dot(e3);
		auto d2 = -e3.Dot(e1);
		auto d3 = -e1.Dot(e2);
		auto c1 = d2 * d3;
		auto c2 = d3 * d1;
		auto c3 = d1 * d2;
		auto c = c1 + c2 + c3;

		auto cc = (p1 * (c2 + c3) + p2 * (c3 + c1) + p3 * (c1 + c2)) / (2.0f * c);

		std::cout << "4.f)\tCircumcenter: x = " << cc.x << ", y = " << cc.y << ", z = " << cc.z << std::endl << std::endl;
	}
}

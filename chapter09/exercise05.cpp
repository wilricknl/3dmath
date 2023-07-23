#include <cmath>
#include <iostream>
#include <vector>

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

	float x;
	float y;
	float z;
};

Vector3 CalculateBestFitPlane(std::vector<Vector3> points)
{
	Vector3 result{ 0.0f, 0.0f, 0.0f };

	if (points.size() > 3)
	{
		Vector3 const* previous = &points[points.size() - 1];
		for (size_t i = 0; i < points.size(); ++i)
		{
			Vector3 const* current = &points[i];
			result.x += (previous->z + current->z) * (previous->y - current->y);
			result.y += (previous->x + current->x) * (previous->z - current->z);
			result.z += (previous->y + current->y) * (previous->x - current->x);
			previous = current;
		}
	}

	return result.Normalize();
}

float CalculateBestFitD(std::vector<Vector3> points, Vector3 n)
{
	Vector3 sum{ 0.0f, 0.0f, 0.0f };
	for (const auto& point : points)
	{
		sum += point;
	}

	return sum.Dot(n) / static_cast<float>(points.size());
}

int main()
{
	std::vector<Vector3> points{
		{ -29.74f, 13.90f, 12.70f },
		{ 11.53f, 12.77f, -9.22f },
		{ 9.16f, 2.34f, 12.67f },
		{ 14.62f, 10.64f, -7.09f },
		{ -3.31f, 3.16f, 18.68f }
	};

	auto result = CalculateBestFitPlane(points);

	// x = -0.254654, y = -0.864239, z = -0.43387
	std::cout << "x = " << result.x << ", y = " << result.y << ", z = " << result.z << std::endl;

	// d = -9.92182
	std::cout << "d = " << CalculateBestFitD(points, result) << std::endl;
}

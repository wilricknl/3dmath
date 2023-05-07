#include <iostream>

struct Quaternion
{
    float w, x, y, z;

    Quaternion inverse() const
    {
        return { w, -x, -y, -z };
    }

    Quaternion operator*(const Quaternion& other) const
    {
        Quaternion result;
        result.w = w * other.w - x * other.x - y * other.y - z * other.z;
        result.x = w * other.x + x * other.w + y * other.z - z * other.y;
        result.y = w * other.y + y * other.w + z * other.x - x * other.z;
        result.z = w * other.z + z * other.w + x * other.y - y * other.x;
        return result;
    }

    Quaternion distance(const Quaternion& other) const
    {
        return other * inverse();
    }
};

void printQuaternion(const Quaternion& q)
{
    std::cout << "[w: " << q.w << " (x: " << q.x << ", y: " << q.y << ", z: " << q.z << ")]\n";
}

int main()
{
    Quaternion q1{ 0.233f, 0.060f, -0.257f, -0.935f };
    Quaternion q2{ -0.752f, 0.286f, 0.374f, 0.459f };
    
    // 8.b: [w:0.332907 (x : 0.253245, y : -0.014544, z : -0.014544)]
    printQuaternion(q1 * q2);

    // 8.c: [w: -0.683339 (x: 0.343485, y: -0.401072, z: -0.500231)]
    printQuaternion(q1.distance(q2));
}

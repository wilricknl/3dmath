#include <cmath>
#include <iostream>

struct Vector3
{
	Vector3 Cross(const Vector3& other) const
	{
		Vector3 result;
		result.x = (y * other.z) - (z * other.y);
		result.y = (z * other.x) - (x * other.z);
		result.z = (x * other.y) - (y * other.x);
		return result;
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

	float x;
	float y;
	float z;
};

struct Mat3
{
  Vector3 x;
  Vector3 y;
  Vector3 z;
};

Vector3 operator*(Vector3 vector, Mat3 matrix) 
{
    auto x = vector.x;
    auto y = vector.y;
    auto z = vector.z;
    
    vector.x = x * matrix.x.x + y * matrix.y.x + z * matrix.z.x; 
    vector.y = x * matrix.x.y + y * matrix.y.y + z * matrix.z.y; 
    vector.z = x * matrix.x.z + y * matrix.y.z + z * matrix.z.z;
	
	return vector;
}

std::ostream& operator<<(std::ostream& out, const Vector3& vector)
{
    out << "[ " << vector.x << ", " << vector.y << ", " << vector.z << "]";
    return out;
}

float rgbToTangentSpace(float value)
{
    return value * 2.0f / 256.0f - 1.0f;
}

void exercise7(
    char exercise,
    Vector3 normalMap,
    Vector3 vertexNormal,
    Vector3 vertexTangent,
    float determinant)
{
    std::cout << exercise << ".) " << std::endl;
    
    // step 1.) convert normal from rgb to tangent space
    normalMap.x = rgbToTangentSpace(normalMap.x);
    normalMap.y = rgbToTangentSpace(normalMap.y);
    normalMap.z = rgbToTangentSpace(normalMap.z);
    std::cout << "\tTangent space surface normal: " << normalMap << std::endl;
    
    // step 2.) determine binormal
    Vector3 vertexBinormal = vertexNormal.Cross(vertexTangent) * determinant;
    std::cout << "\tVertex binormal: " << vertexBinormal << std::endl;
    
    // step 3.) model-space coordinates of the per-texel surface normal
    Mat3 matrix{ vertexTangent, vertexBinormal, vertexNormal };
    Vector3 modelSpaceSurfaceNormal = normalMap * matrix;
    std::cout << "\tModel-space per-texel surface normal: " << modelSpaceSurfaceNormal << std::endl;
}

int main()
{
    //a.) 
    //	Tangent space surface normal: [ 0, 0.992188, 0]
    //	Vertex binormal: [ 0.576912, -0.576912, 0.576912]
    //	Model-space per-texel surface normal: [ 0.572405, -0.572405, 0.572405]
    exercise7(
        'a',
        Vector3{ 128.0f, 255.0f, 128.0f },
        Vector3{ 0.408f, -0.408f, -0.816f },
        Vector3{ 0.707f, 0.707f, 0.0f },
        1.0f);
    
    //b.) 
    //	Tangent space surface normal: [ -0.171875, 0.210938, 0.953125]
    //	Vertex binormal: [ -0, -0, 1]
    //	Model-space per-texel surface normal: [ -0.171875, 0.953125, 0.210938]
    exercise7(
        'b',
        Vector3{ 106.0f, 155.0f, 250.0f },
        Vector3{ 0.0f, 1.0f, 0.0f },
        Vector3{ 1.0f, 0.0f, 0.0f },
        -1.0f);
    
    //c.) 
    //	Tangent space surface normal: [ 0, 0.703125, 0.703125]
    //	Vertex binormal: [ -0, 0.894, 0.447]
    //	Model-space per-texel surface normal: [ 0.703125, 0.628594, 0.314297]
    exercise7(
        'c',
        Vector3{ 128.0f, 218.0f, 218.0f },
        Vector3{ 1.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.447f, -0.894f },
        1.0f);
        
    //d.) 
    //	Tangent space surface normal: [ 0.820312, -0.546875, 0.132812]
    //	Vertex binormal: [ -0.063825, -0.785986, -0.615446]
    //	Model-space per-texel surface normal: [ 0.864186, 0.385625, 0.307033]
    exercise7(
        'd',
        Vector3{ 233.0f, 58.0f, 145.0f },
        Vector3{ 0.154f, -0.617f, 0.772f },
        Vector3{ 0.986f, 0.046f, -0.161f },
        -1.0f);
    
    return 0;
}

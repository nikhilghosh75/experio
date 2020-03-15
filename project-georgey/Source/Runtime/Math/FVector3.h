#include <string>
using namespace std;

struct FVector3
{
public:
    float x;
    float y;
    float z;

    FVector3();
    FVector3(float x, float y, float z);
    FVector3(float x, float y);

    static float Magnitude(const FVector3& V);
    static float SqrMagnitude(const FVector3& V);

    static float Distance(const FVector3& V1, const FVector3& V2);
    static float SqrDistance(const FVector3& V1, const FVector3& V2);

    static FVector3 Normalized(const FVector3& V);

    static float Dot(const FVector3& V1, const FVector3& V2);
    static FVector3 Cross(const FVector3& V1, const FVector3& V2);

    static bool Coincident(const FVector3& V1, const FVector3& V2, float Threshold=0.001f);
    static bool IsZero(const FVector3& V, float threshold=0.001f);
    static bool IsNormalized(const FVector3& V);

    static float GetMax(const FVector3& V);
    static float GetMin(const FVector3& V);
    static FVector3 Abs(const FVector3& V);
    static FVector3 Reciprocal(const FVector3& V);

    static string ToString(const FVector3& V, const int numDigits = 5);

    operator string() { return FVector3::ToString(*this); }

    const FVector3 operator+(const FVector3& V);
    FVector3 operator+=(const FVector3& V);
    const FVector3 operator-(const FVector3& V);
    FVector3 operator-=(const FVector3& V);
    const FVector3 operator*(float f);
    FVector3 operator*=(float f);
    const FVector3 operator/(const float f);
    FVector3 operator/=(float f);
};
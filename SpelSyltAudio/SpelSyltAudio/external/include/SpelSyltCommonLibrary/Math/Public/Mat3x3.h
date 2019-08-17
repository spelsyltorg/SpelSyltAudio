#pragma once

namespace CL
{
	class CMat3x3
	{
	public:
		CMat3x3();
		CMat3x3(const CMat3x3& InOther);
		CMat3x3(CMat3x3&& InOther) noexcept;

		void MakeIdentity();
		bool IsIdentity() const;

		void Transpose();
		CMat3x3 GetTransposed() const;

		void Invert();
		CMat3x3 GetInverse() const;

		static void MakeXScale(CMat3x3& OutScaleMatrix, float InScale);
		static void MakeYScale(CMat3x3& OutScaleMatrix, float InScale);
		static void MakeZScale(CMat3x3& OutScaleMatrix, float InScale);

		static void MakeXRotation(CMat3x3& OutRotationMatrix, float InRadians);
		static void MakeYRotation(CMat3x3& OutRotationMatrix, float InRadians);
		static void MakeZRotation(CMat3x3& OutRotationMatrix, float InRadians);

		CL::CMat3x3 operator*(const CMat3x3& InRHS) const;
		CL::CMat3x3 operator*(const float InRHS) const;

		void operator=(CMat3x3&& InRHS) noexcept;
		void operator=(const CMat3x3& InRHS);
		void operator*=(const CMat3x3& InRHS);
		void operator*=(const float InRHS);

		inline float& M11() { return Matrix[0][0]; };
		inline float& M21() { return Matrix[0][1]; };
		inline float& M31() { return Matrix[0][2]; };
		inline float& M12() { return Matrix[1][0]; };
		inline float& M22() { return Matrix[1][1]; };
		inline float& M32() { return Matrix[1][2]; };
		inline float& M13() { return Matrix[2][0]; };
		inline float& M23() { return Matrix[2][1]; };
		inline float& M33() { return Matrix[2][2]; };

		inline float M11() const { return Matrix[0][0]; };
		inline float M21() const { return Matrix[0][1]; };
		inline float M31() const { return Matrix[0][2]; };
		inline float M12() const { return Matrix[1][0]; };
		inline float M22() const { return Matrix[1][1]; };
		inline float M32() const { return Matrix[1][2]; };
		inline float M13() const { return Matrix[2][0]; };
		inline float M23() const { return Matrix[2][1]; };
		inline float M33() const { return Matrix[2][2]; };

		inline float& X() { return M13(); };
		inline float& Y() { return M23(); };
		inline float& Z() { return M33(); };

		inline float X() const { return M13(); };
		inline float Y() const { return M23(); };
		inline float Z() const { return M33(); };

	private:
		float Matrix[3][3];
	};
}
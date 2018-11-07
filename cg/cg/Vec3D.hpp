#ifndef CG_VEC3D_HPP
#define CG_VEC3D_HPP

#include <cstdint>

#include "Mat4x4.hpp"

namespace cg
{
	template<class Elem>
	struct BasicVec3D
	{
		using ElementType = Elem;

		constexpr BasicVec3D() noexcept = default;

		constexpr BasicVec3D(const BasicVec3D&) noexcept = default;

		constexpr BasicVec3D& operator=(const BasicVec3D&) noexcept = default;

		constexpr explicit BasicVec3D(Elem x, Elem y, Elem z) noexcept :
			x(x), y(y), z(z)
		{
		}

		template<typename Other>
		constexpr explicit BasicVec3D(const BasicVec3D<Other>& right) noexcept :
			x(static_cast<Other>(right.x)), y(static_cast<Other>(right.y)), z(static_cast<Other>(right.z))
		{
		}

		std::conditional_t<std::is_floating_point_v<Elem>, Elem, float> length() const noexcept
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		constexpr BasicVec3D& operator*=(const BasicMat4x4<Elem>& m) noexcept
		{
			float cx = x, cy = y, cz = z;

			cx = x * m.get<0, 0>() + y * m.get<1, 0>() + z * m.get<2, 0>() + m.get<3, 0>();
			cy = x * m.get<0, 1>() + y * m.get<1, 1>() + z * m.get<2, 1>() + m.get<3, 1>();
			cz = x * m.get<0, 2>() + y * m.get<1, 2>() + z * m.get<2, 2>() + m.get<3, 2>();
			float w = x * m.get<3, 0>() + y * m.get<3, 1>() + z * m.get<3, 2>() + m.get<3, 3>();

			if (w != 0.0f)
			{
				cx /= w;
				cy /= w;
				cz /= w;
			}

			x = cx;
			y = cy;
			z = cz;

			return *this;
		}

		constexpr BasicVec3D operator*(const BasicMat4x4<Elem>& m) const noexcept
		{
			auto i = *this;
			i *= m;
			return i;
		}

		constexpr BasicVec3D operator+=(const BasicVec3D& right) noexcept
		{
			x += right.x;
			y += right.y;
			z += right.z;
			return *this;
		}

		constexpr BasicVec3D operator-=(const BasicVec3D& right) noexcept
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			return *this;
		}

		constexpr BasicVec3D operator*=(float right) noexcept
		{
			x *= right;
			y *= right;
			z *= right;
			return *this;
		}

		constexpr BasicVec3D operator/=(float right) noexcept
		{
			x /= right;
			y /= right;
			z /= right;
			return *this;
		}

		constexpr BasicVec3D operator+(const BasicVec3D& m) const noexcept
		{
			auto i = *this;
			i += m;
			return i;
		}

		constexpr BasicVec3D operator-(const BasicVec3D& m) const noexcept
		{
			auto i = *this;
			i -= m;
			return i;
		}

		constexpr BasicVec3D operator*(float m) const noexcept
		{
			auto i = *this;
			i *= m;
			return i;
		}

		constexpr BasicVec3D operator/(float m) const noexcept
		{
			auto i = *this;
			i /= m;
			return i;
		}

		Elem x{},
			 y{},
			 z{};
	};

	template<class Elem>
	constexpr BasicVec3D<Elem> scale(const BasicVec3D<Elem>& left, const BasicVec3D<Elem>& right) noexcept
	{
		return BasicVec3D<Elem>(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	using iVec3D = BasicVec3D<std::int32_t>;
	using uVec3D = BasicVec3D<std::uint32_t>;
	using Vec3D = BasicVec3D<float>;
	using dVec3D = BasicVec3D<double>;
	using ldVec3D = BasicVec3D<long double>;
}

#endif
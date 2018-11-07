#ifndef CG_MAT4X4_HPP
#define CG_MAT4X4_HPP

#include "Vec2D.hpp"
#include <utility>

namespace cg
{
	template<class Elem>
	class BasicMat4x4
	{
	public:
		constexpr BasicMat4x4() noexcept = default;

		constexpr BasicMat4x4(const BasicMat4x4&) noexcept = default;

		constexpr BasicMat4x4& operator=(const BasicMat4x4&) noexcept = default;

		template<typename... Args>
		constexpr explicit BasicMat4x4(Args... items) noexcept
		{
			Elem arr[] = { items... };

			auto x = std::begin(arr);

			for (Elem* s = mat,* e = mat + 16; s != e; ++s, ++x)
			{
				*s = *x;
			}
		}
		
		constexpr Elem& operator[](const iVec2D& idx) noexcept
		{
			if (idx.x >= 4 || idx.y >= 4)
				terminate();
			return mat[4 * idx.y + idx.x];
		}

		constexpr const Elem& operator[](const iVec2D& idx) const noexcept
		{
			if (idx.x >= 4 || idx.y >= 4)
				terminate();
			return mat[4 * idx.y + idx.x];
		}

		template<size_t x, size_t y>
		constexpr Elem& get() noexcept
		{
			static_assert(x < 4 && y < 4, "subscription out of range.");
			return mat[4 * y + x];
		}

		template<size_t x, size_t y>
		constexpr const Elem& get() const noexcept
		{
			static_assert(x < 4 && y < 4, "subscription out of range.");
			return mat[4 * y + x];
		}

	private:
		Elem mat[16] = {};

	};

	using Mat4x4 = BasicMat4x4<float>;
	using dMat4x4 = BasicMat4x4<double>;
	using ldMat4x4 = BasicMat4x4<long double>;
	using iMat4x4 = BasicMat4x4<std::int32_t>;
	using uMat4x4 = BasicMat4x4<std::uint32_t>;

}

#endif 

#ifndef CG_VEC2D_HPP
#define CG_VEC2D_HPP

#include <cstdint>

namespace cg
{
	template<class Elem>
	struct BasicVec2D
	{
		using ElementType = Elem;

		constexpr BasicVec2D() noexcept = default;

		constexpr BasicVec2D(const BasicVec2D&) noexcept = default;

		constexpr BasicVec2D& operator=(const BasicVec2D&) noexcept = default;

		constexpr explicit BasicVec2D(Elem x, Elem y) noexcept :
			x(x), y(y)
		{
		}
		
		template<typename Other>
		constexpr explicit BasicVec2D(const BasicVec2D<Other>& right) noexcept :
			x(static_cast<Other>(right.x)), y(static_cast<Other>(right.y))
		{
		}


		std::conditional_t<std::is_floating_point_v<Elem>, Elem, float> length() const noexcept
		{
			return std::sqrt(x * x + y * y);
		}

		Elem x{},
			 y{};
	};

	using iVec2D = BasicVec2D<std::int32_t>;
	using uVec2D = BasicVec2D<std::uint32_t>;
	using Vec2D = BasicVec2D<float>;
	using dVec2D = BasicVec2D<double>;
	using ldVec2D = BasicVec2D<long double>;
}

#endif
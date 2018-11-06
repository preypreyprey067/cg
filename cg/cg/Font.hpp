#ifndef CG_FONT_HP
#define CG_FONT_HPP

#include "Vec2D.hpp"
#include <cstdint>
#include <string>
#include <Windows.h>

namespace cg
{

	struct Font
	{
		enum class Family : std::uint16_t
		{
			modern = FF_MODERN,
			decorative = FF_DECORATIVE,
			swiss = FF_SWISS,
			dontCare = FF_DONTCARE,
			script = FF_SCRIPT,
			roman = FF_ROMAN
		};

		enum class Weight : std::uint16_t
		{
			normal = FW_NORMAL,
			bold = FW_BOLD,
			heavy = FW_HEAVY,
			black = heavy, 
			extraBold = FW_EXTRABOLD,
			light = FW_LIGHT,
			thin = FW_THIN,
			extraLight = FW_EXTRALIGHT,
			semiBold = FW_SEMIBOLD,
			dontCare = FW_DONTCARE,
			medium = FW_MEDIUM
		};

		Font() noexcept = default;

		Font(const Font&) = default;

		Font& operator=(const Font&) = default;

		Font& operator=(Font&& right)
		{
			size = std::move(right.size);
			family = std::move(right.family);
			weight = std::move(right.weight);
			name = std::move(right.name);
		}

		explicit Font(const cg::iVec2D& sz, 
			Family fm = Family::dontCare, Weight fw = Weight::normal,
			const std::string& nm = "Consolas") :
			size(sz), family(fm), weight(fw), name(nm)
		{
		}

		cg::iVec2D size{};
		Family family{};
		Weight weight{};
		std::string name{};
	};
}

#endif
#ifndef CG_WINDOW_HP
#define CG_WINDOW_HPP

#include <string>
#include <functional>
#include "Vec2D.hpp"
#include "Font.hpp"

#include "cgimpl.hpp"

#ifdef _MSC_VER
#	pragma warning(disable : 4996)
#endif


namespace cg
{
	class Window
	{
	public:
		Window(const Window&) = delete;

		Window& operator=(const Window&) = delete;

		explicit Window(const std::string& name = "", const cg::iVec2D& size = cg::iVec2D(), 
			const cg::Font& font = cg::Font()) :
			sName(name), vSize(size), fFont(font)
		{
		}

		const std::string& name() const
		{
			return sName;
		}

		cg::Window& name(const std::string& val)
		{
			sName = val;
			return *this;
		}

		cg::iVec2D size() const
		{
			return vSize;
		}

		cg::Window& size(const cg::iVec2D& val)
		{
			vSize = val;
			return *this;
		}

		const cg::Font& font() const
		{
			return fFont;
		}

		cg::Window& font(const cg::Font& val)
		{
			fFont = val;
			return *this;
		}
		
		bool create()
		{
			if (ximplcg::__hOut == INVALID_HANDLE_VALUE)
			{
				throw std::runtime_error("handle was invalid.");
				return false;
			}

			rWnd = { 0, 0, 1, 1 };
			SetConsoleWindowInfo(ximplcg::__hOut, TRUE, &rWnd);

			COORD cSize{ static_cast<short>(vSize.x), static_cast<short>(vSize.y) };

			if (!SetConsoleScreenBufferSize(ximplcg::__hOut, cSize))
			{
				throw std::runtime_error("error setting screen buffer size.");
				return false;
			}

			if (!SetConsoleActiveScreenBuffer(ximplcg::__hOut))
			{
				throw std::runtime_error("error setting active screen buffer.");
				return false;
			}

			CONSOLE_FONT_INFOEX cfFont{ sizeof(CONSOLE_FONT_INFOEX), 0, 
				{ static_cast<SHORT>(fFont.size.x), static_cast<SHORT>(fFont.size.y)},
				static_cast<UINT>(fFont.family), static_cast<UINT>(fFont.weight), { 0 } };

			mbstowcs(cfFont.FaceName, fFont.name.c_str(), 32);

			if (!SetCurrentConsoleFontEx(ximplcg::__hOut, FALSE, &cfFont))
			{
				throw std::runtime_error("error setting screen buffer info.");
				return false;
			}


			CONSOLE_SCREEN_BUFFER_INFO iBuf;

			if (!GetConsoleScreenBufferInfo(ximplcg::__hOut, &iBuf))
			{
				throw std::runtime_error("error setting screen buffer info.");
				return false;
			}

			if (static_cast<SHORT>(vSize.x) > iBuf.dwMaximumWindowSize.X || static_cast<SHORT>(vSize.y) > iBuf.dwMaximumWindowSize.Y)
			{
				throw std::runtime_error("window size is too big.");
				return false;
			}

			rWnd = { 0, 0, (short)vSize.x - 1, (short)vSize.y - 1 };

			if (!SetConsoleWindowInfo(ximplcg::__hOut, TRUE, &rWnd))
			{
				throw std::runtime_error("error setting window rect.");
				return false;
			}

			/*if (!SetConsoleMode(__hIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
			{
				throw std::runtime_error("error setting console mode.");
				return false;
			}*/
			
			ximplcg::__cBsz = cSize;
			ximplcg::__srWndr = rWnd;

			std::uint16_t w = vSize.x * vSize.y;

			ximplcg::__ciBuffer = new CHAR_INFO[w];
			std::fill(ximplcg::__ciBuffer, ximplcg::__ciBuffer + w, CHAR_INFO{ 0, 0 });

			SetConsoleTitle(sName.c_str());

			ximplcg::__bufFlush();

			return true;
		}

		~Window()
		{
			delete[] ximplcg::__ciBuffer;
		}

	private:
		std::string sName{};
		cg::iVec2D vSize{};
		cg::Font fFont{};
		SMALL_RECT rWnd;
		

	};
}

#endif
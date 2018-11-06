#include "Window.hpp"
#include "Vec3D.hpp"


#undef near
#undef far

struct triangle
{
	cg::Vec3D a;
	cg::Vec3D b;
	cg::Vec3D c;
};

triangle mCube[] = 
{
	{ cg::Vec3D{0.0f, 0.0f, 0.0f}, cg::Vec3D{ 0.0f, 1.0f, 0.0f }, cg::Vec3D{ 1.0f, 1.0f, 0.0f } },
	{ cg::Vec3D{0.0f, 0.0f, 0.0f}, cg::Vec3D{ 1.0f, 1.0f, 0.0f }, cg::Vec3D{ 1.0f, 0.0f, 0.0f } },
	{ cg::Vec3D{1.0f, 0.0f, 0.0f}, cg::Vec3D{ 1.0f, 1.0f, 0.0f }, cg::Vec3D{ 1.0f, 1.0f, 1.0f } },
	{ cg::Vec3D{1.0f, 0.0f, 0.0f}, cg::Vec3D{ 1.0f, 1.0f, 1.0f }, cg::Vec3D{ 1.0f, 0.0f, 1.0f } },
	{ cg::Vec3D{1.0f, 0.0f, 1.0f}, cg::Vec3D{ 1.0f, 1.0f, 1.0f }, cg::Vec3D{ 0.0f, 1.0f, 1.0f } },
	{ cg::Vec3D{1.0f, 0.0f, 1.0f}, cg::Vec3D{ 0.0f, 1.0f, 1.0f }, cg::Vec3D{ 0.0f, 0.0f, 1.0f } },
	{ cg::Vec3D{0.0f, 0.0f, 1.0f}, cg::Vec3D{ 0.0f, 1.0f, 1.0f }, cg::Vec3D{ 0.0f, 1.0f, 0.0f } },
	{ cg::Vec3D{0.0f, 0.0f, 1.0f}, cg::Vec3D{ 0.0f, 1.0f, 0.0f }, cg::Vec3D{ 0.0f, 0.0f, 0.0f } },
	{ cg::Vec3D{0.0f, 1.0f, 0.0f}, cg::Vec3D{ 0.0f, 1.0f, 1.0f }, cg::Vec3D{ 1.0f, 1.0f, 1.0f } },
	{ cg::Vec3D{0.0f, 1.0f, 0.0f}, cg::Vec3D{ 1.0f, 1.0f, 1.0f }, cg::Vec3D{ 1.0f, 1.0f, 0.0f } },
	{ cg::Vec3D{1.0f, 0.0f, 1.0f}, cg::Vec3D{ 0.0f, 0.0f, 1.0f }, cg::Vec3D{ 0.0f, 0.0f, 0.0f } },
	{ cg::Vec3D{1.0f, 0.0f, 1.0f}, cg::Vec3D{ 0.0f, 0.0f, 0.0f }, cg::Vec3D{ 1.0f, 0.0f, 0.0f } }
};

int main()
{
	cg::Window wnd("hello world", cg::iVec2D(425, 150),
		cg::Font(cg::iVec2D(4, 4), cg::Font::Family::dontCare, cg::Font::Weight::bold , "Lucida Console"));

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;


	float near = 0.1f;
	float far = 1000.0f;
	float fovrad = 60.0f;
	float aspect = static_cast<float>(wnd.size().y) / wnd.size().x + 0.1f;
	float fovr = 1.0f / std::tan(fovrad * 0.5f / 180.0f * 3.14159f);

	cg::Mat4x4 mat;

	mat.get<0, 0>() = aspect * fovr;
	mat.get<1, 1>() = fovr;
	mat.get<2, 2>() = (-far / (far - near));
	mat.get<2, 3>() = (-far * near) / (far - near);
	mat.get<3, 2>() = -1.0f;
	mat.get<3, 3>() = 0.0f;

	

	if (wnd.create())
	{


		while (true)
		{
			x += 0.1f;
			y += 0.1f;
			z += 0.1f;

			cg::Mat4x4 matTrans
			{
				1.0f, 0.0f, 0.0f, x,
				0.0f, 1.0f, 0.0f, y,
				0.0f, 0.0f, 1.0f, z,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			ximplcg::__bufClr({ 0, 0 });


			for (const triangle& tri : mCube)
			{
				
				triangle triProj = { tri.a * matTrans * mat, tri.b  * matTrans * mat, tri.c * matTrans* mat };

				triProj.a.x += 1.0f;
				triProj.a.y += 1.0f;
				triProj.a = cg::scale(triProj.a,
					cg::Vec3D(static_cast<float>(wnd.size().x), static_cast<float>(wnd.size().y), 1) * 0.5f);
				triProj.b.x += 1.0f;
				triProj.b.y += 1.0f;
				triProj.b = cg::scale(triProj.b,
					cg::Vec3D(static_cast<float>(wnd.size().x), static_cast<float>(wnd.size().y), 1) * 0.5f);
				triProj.c.x += 1.0f;
				triProj.c.y += 1.0f;
				triProj.c = cg::scale(triProj.c,
					cg::Vec3D(static_cast<float>(wnd.size().x), static_cast<float>(wnd.size().y), 1) * 0.5f);



				ximplcg::__bufDrt(triProj.a.x, triProj.a.y, triProj.b.x, triProj.b.y, triProj.c.x, triProj.c.y, { 0, 255 });
			}

			ximplcg::__bufFlush();
		}
	}

}

#include "WinApp.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "RenderSystem.h"

#include "GameManager.h"

#include <string>

namespace game
{
	struct Object
	{
		float x;
		float y;
		float size;
		float speed;

		COLORREF color;

		void SetPos(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		void Move(float x, float y)
		{
			this->x += x;
			this->y += y;
		}

		void MoveByDeltaTime(float x, float y)
		{
			this->x += x * time::GetDeltaTime();
			this->y += y * time::GetDeltaTime();
		}
	};

	Object player = 
		{ global::GetWinApp().GetWidth() / 2 
		, global::GetWinApp().GetHeight() / 2
		, 10, 0.1f, RGB(255, 255, 0) };
	HBITMAP hTestBitmap = nullptr;

	const int bludeCircleMax = 100;
	int blueCircleCount = 0;
	Object blueCircles[bludeCircleMax];

	GameManager* GameManager::instance = nullptr; // 스태틱변수는 반드시 초기화 되어야함
	GameManager::GameManager() {}

	GameManager::~GameManager() {}

	void GameManager::Initialize()
	{
		input::InitInput();
		time::InitTime();
		render::InitRender();
	}

	void UpdatePlayer()
	{
		// 게임 로직은 여기에 추가
		if (input::IsKey('A'))
		{
			player.Move(-player.speed, 0);
		}
		else if (input::IsKey('D'))
		{
			player.Move(player.speed, 0);
		}
		if (input::IsKey('W'))
		{
			player.Move(0, -player.speed);
		}
		else if (input::IsKey('S'))
		{
			player.Move(0, player.speed);
		}
	}

	void UpdateBlueCircle()
	{
		const input::MouseState& mouse = input::GetMouseState();
		const input::MouseState& prevmouse = input::GetPrevMouseState();

		if (input::IsSame(mouse, prevmouse))
		{
			return;
		}

		if (blueCircleCount < bludeCircleMax && mouse.left)
		{
			blueCircles[blueCircleCount].SetPos(mouse.x, mouse.y);
			blueCircles[blueCircleCount].color = RGB(0, 0, 255);
			blueCircles[blueCircleCount].size = 10;
			blueCircles[blueCircleCount].speed = 0;
			blueCircleCount++;
		}
	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		input::UpdateMouse();

		UpdatePlayer();
		UpdateBlueCircle();

		input::ResetInput();
	}



	void GameManager::FixeUpdate()
	{
		static ULONGLONG elapsedTime;

		elapsedTime += time::GetDeltaTime();

		while (elapsedTime >= 20) //0.02초
		{
			++m_FixedUpdateCount;

			elapsedTime -= 20;
		}
	}

	void GameManager::Render() 
	{
		render::BeginDraw();

		DrawFPS();
		DrawSomething();
		DrawPlayer();

		render::EndDraw();
	}

	void GameManager::Finalize() 
	{
		render::ReleaseRender();
	}

	void GameManager::Run()
	{
		MSG msg;
		// 게임에 필요한 리소르를 미리 로드!
		Load();

		while (true)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;

				if (msg.message == WM_KEYDOWN)
				{
					input::KeyDown(msg.wParam);
				}
				else if (msg.message == WM_KEYUP)
				{
					input::KeyUp(msg.wParam);
				}
				else
				{
					DispatchMessage(&msg);
				}
			}
			else
			{
				time::UpdateTime();
				FixeUpdate();
				Update();
				Render();
			}
		}

		UnLoad();
	}

	void GameManager::Load()
	{
		hTestBitmap = render::LoadImdage("Mario.bmp");
	}

	void GameManager::UnLoad()
	{
		render::ReleaseImage(hTestBitmap);
	}


	GameManager* GameManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
		}
		return instance;
	}

	void GameManager::DestroyInstance() {}

	void GameManager::DrawFPS()
	{
		static double elapsedTime;
		static int UpdateCount;
		static int FixedUpdateCount;

		elapsedTime += time::GetDeltaTime();

		if (elapsedTime >= 1000)
		{
			elapsedTime = 0.f;
			UpdateCount = m_UpdateCount;
			FixedUpdateCount = m_FixedUpdateCount;

			m_UpdateCount = 0;
			m_FixedUpdateCount = 0;
		}

		std::string str = "FPS: " + std::to_string(time::GetFrameRate());
		str += "           Update " + std::to_string(UpdateCount);
		str += "           FixedUpdate " + std::to_string(FixedUpdateCount);

		render::DrawText(10, 10, str.c_str(), RGB(255, 0, 0));

	}
	void GameManager::DrawPlayer()
	{
		render::DrawCircle(player.x, player.y, player.size, player.color);
	}

	void GameManager::DrawSomething()
	{
		for (int i = 0; i < blueCircleCount; i++)
		{
			render::DrawCircle(blueCircles[i].x, blueCircles[i].y, blueCircles[i].size, blueCircles[i].color);
		}
		render::DrawBitmap(50, 50, hTestBitmap);
		render::DrawLine(player.x - 50, player.y + 50, player.x + 50, player.y + 50, RGB(255, 0, 0));
		render::DrawRect(player.x - 25, player.y - 25, 50, 50, RGB(255, 0, 255));

		
	}
}
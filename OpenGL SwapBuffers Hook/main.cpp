#include "phook.h"

PTR SwapBuffersAddr;
wglSwapBuffers oSwapBuffers;

 void DrawFilledRect(float x, float y, float width, float height)
 {
 	glColor3ub(255, 0, 0);
 	glBegin(GL_QUADS);
 	glVertex2f(x, y);
 	glVertex2f(x + width, y);
 	glVertex2f(x + width, y + height);
 	glVertex2f(x, y + height);
 	glEnd();

 }



bool init = false;
BOOL __stdcall PHook::hkSwapBuffers(_In_ HDC hdc)
{
	if (!init)
	{
		MessageBox(NULL, "Success!", "SwapBuffers Hook", MB_OK);
		init = true;
	}
	PHook::SetupOrtho();
	//Draw Here
	DrawFilledRect(100, 100, 100, 100);
	
	
	//PHook::Restore(); breaks osu!
	return oSwapBuffers(hdc);
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PHook::Init, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PHook::Shutdown, hMod, 0, nullptr);
		break;
	}
	return TRUE;
}

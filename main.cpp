#include <Windows.h>
#include <iostream>
#define OFFSET_XDMG 0x14187e47b // 8b 8a 50 01 00 00 49 8b 50 20 e9

int main()
{
	DWORD pid;
	GetWindowThreadProcessId(FindWindowA(NULL, "star wars battlefront ii"), &pid);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	byte* shellcode = new byte[6]{ 0xb9, 0x00, 0x00, 0x00, 0x00, 0x90 };
	for (;;)
	{
		int newDamage;
		std::cout << "enter new damage:\n>";
		std::cin >> newDamage;
		memcpy(shellcode + 1, &newDamage, 4);
		WriteProcessMemory(hProc, (LPVOID)OFFSET_XDMG, shellcode, 6, nullptr);
	}
}
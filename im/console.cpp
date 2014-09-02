#include <stdio.h>
#include <Windows.h>
#include "console.h"
#include "util/log.h"


win_console::win_console()
{
	memset(line, 0, 4096);
	mark = 0;

	cb = NULL;

	move_to_bottom();
}
win_console::~win_console()
{}

void win_console::clear_input_line(void)
{
	move_to_bottom();

	COORD size = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
	for (int i=0; i<size.X; i++)
		DPRINT_NOENDL(LOG_INFO, " ");
	move_to_bottom();
}

void win_console::move_to_bottom(void)
{
	COORD size = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

	size.X = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), size);
}

void win_console::move_to_top(void)
{
	COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void win_console::print_input_line(const char* cmd)
{
	clear_input_line();
	if (cmd) {
		DPRINT_NOENDL(LOG_INFO, "%s", cmd);
	}
	else {
		DPRINT_NOENDL(LOG_INFO, "");
	}
}

void win_console::print_output(const char* text)
{
	move_to_top();

	DPRINT(LOG_INFO, "%s", text);
}

void win_console::onkey(KEY_EVENT_RECORD k)
{
	if(k.bKeyDown) {
		char c = k.uChar.AsciiChar;
		if (c == 13) {
			/* Enter */
			line[mark] = '\0';

			// process
			if (cb)
				cb(line);

			memset(line, 0, 4096);
			mark = 0;
			print_input_line(NULL);
			return;
		}
		else if (c == 8) {
			/* Backspace */
			line[--mark] = '\0';
		}
		else {
			line[mark++] = c;
		}
		print_input_line(line);
	}
}

void win_console::set_process_cb(process_command_cb cb)
{
	this->cb = cb;
}

void win_console::run_loop(void)
{
	const char* cmdtitle = ">>>";
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1) {
// 		if (!WriteFile(hout, cmdtitle, lstrlen(cmdtitle), NULL, NULL))
// 			return;
		DPRINT_NOENDL(LOG_INFO, "%s", cmdtitle);

		DWORD len = 0;
		if (!ReadFile(hin, line, 4095, &len, NULL))    // not overlapped 
			break;

		
		/* 最后两个字符\r\n，删掉，并追加结束符 */
		line[len-2] = '\0';

		if (strlen(line) <= 0)
			continue;

		if (cb)
			cb(line);

		if (line[0] == 'q') break; 
	} 
}
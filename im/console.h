#pragma once

#include <Windows.h>

typedef void (*process_command_cb)(const char* cmd);

class win_console {
	char	line[4096];
	int		mark;
	void	onkey(KEY_EVENT_RECORD k);

	void	clear_input_line(void);
	void	print_input_line(const char* cmd);

	void	move_to_bottom(void);
	void	move_to_top(void);

	process_command_cb cb;
public:
	win_console();
	~win_console();

	void	set_process_cb(process_command_cb cb);

	void	print_output(const char* text);

	void	run_loop(void);
};
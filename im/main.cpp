#include <stdio.h>
#include "libim/core.h"
#include "mconn.h"
#include "util/error_process.h"
#include "util/config.h"

int main(int argc, char** argv)
{
	g_im_core.init();

	test_conn();


	g_im_core.quit();
	return 0;
}
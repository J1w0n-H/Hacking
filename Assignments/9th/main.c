#include <stdio.h>

static int stt_data = 1;
int ext_data;

static int Stt_func(){
	printf("static function\n");
}
int Ext_func(){
	printf("extern function\n");
}

int main()
{
	Stt_func();
	Ext_func();
	printf("static variable stt_data: %d\n", stt_data);
	printf("extern variable ext_data: %d\n", ext_data);
}

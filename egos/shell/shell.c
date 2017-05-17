#include "shell.h"
#include "keyboard.h"

#define INVALID_CODE -1

static int id = 0;

struct user{

};


void init_shell(){
	while(1){
		printk(">%d $:", id);
		while(1){
			char c = getChar();
			if (c != INVALID_CODE) {
				printk("%c", c);
			}
			if (c == '\n'){
				break;
			}
		}
	}
}
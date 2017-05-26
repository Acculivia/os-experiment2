#include "buff.h"
#include "string.h"
#include "io.h"

/*
buff缓冲区的作用是进行io读写
*/
char * buffer[256];

int write_addr;

int buff_max_addr; 

int addr_to_lba(void * addr){
	int iaddr = (int)addr / 128;
	return iaddr;
}

void buff_init(){
	write_addr = 0;
	buff_max_addr = 0;
}

void buff_write(int addr, void * src, int len){
	write_addr = addr;
	char * ad = (char *) src;
	while(len >= 0){
		memcpy(buffer, src, 256);
		write_sect(2, addr, buffer);
		len -= 256;
		addr += 256;
	}




}

void buff_clear(){
	buff_max_addr = 0;
}

void buff_flush(){

}

void buff_read(void * addr, int len){

}

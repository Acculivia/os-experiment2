#ifndef INCLUDE_IO
#define INCLUDE_IO

#define SIZE 256

//从硬盘读取一个扇区
void * read_sect(unsigned char count, int lba, void * buff);

//向硬盘写入一个扇区
void * write_sect(unsigned char count, int lba, void * buff);

void test_io();

#endif
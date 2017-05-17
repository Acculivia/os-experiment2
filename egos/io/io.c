#include "io.h"

/*
//io的主要部分就是如何从硬盘中读取和写入扇区。网上很多地方推荐
//的办法是切换回rmode然后使用bios调用，因为“其它方法会复杂一些”。
//诚然如果使用汇编去编写的话，代码量是有血长；但是如下所示，C语言
//已经大大地把代码量给简化了，最终也无非调用一下硬件的api而已
//
//另，在idt部分看到了与ide相关的中断函数。觉得或许应当填到对应的地方上，
//但是因无经验而无头绪。
*/

void * read_sect(unsigned char count, int lba, void * buff){
	//printk("read from disk: \n");
	while(inb(0x1f7) & 0xc0 != 0x40)
		;

	outb(0x1f2, count);
	outb(0x1f3, (unsigned char)lba);//lbalow
	outb(0x1f4, (unsigned char)(lba >> 8));//lbamid
	outb(0x1f5, (unsigned char)(lba >> 16));//lbahigh
	outb(0x1f6, 0xe0 | ((lba >> 24) & 0x0F));//controls + lba 
	outb(0x1f7, 0x20);

	while(inb(0x1f7) & 0xc0 != 0x40)
		;

	insl(0x1f0, buff, SIZE);
}

void * write_sect(unsigned char count, int lba, void * buff){
	//printk("write to disk: \n");
	while(inb(0x1f7) & 0xc0 != 0x40)
		;

	outb(0x1f2, count);
	outb(0x1f3, (unsigned char)lba);//lbalow
	outb(0x1f4, (unsigned char)(lba >> 8));//lbamid
	outb(0x1f5, (unsigned char)(lba >> 16));//lbahigh
	outb(0x1f6, 0xe0 | ((lba >> 24) & 0x0F));//controls + lba 
	outb(0x1f7, 0x30);

	while(inb(0x1f7) & 0xc0 != 0x40)
		;

	outsl(0x1f0, buff, SIZE);
}

//测试通过  哦啦啦啦啦啦～～～～
//发现网上很多教程不论新旧都是在此处打断我后来总算找到资料的时候在想
//为什么这么简单的东西那些人就是不愿意搞出来呢还是因为
//我搜寻资料的能力太强？
void test_io(){
	char * a[256];
	for(int i = 0; i < 256; ++i) a[i] = i;

	for(int i = 0; i < 100; ++i) printk("%x ", a[i]);

	printk("\n");

	write_sect(1, 0, (void *)a);

	for(int i = 0; i < 256; ++i) a[i] = 0xffff;


	write_sect(1, 1, (void *)a);
	read_sect(1, 0, (void *)a);
	//read_sect(1, 1, (void *)a);

	for(int i = 0; i < 100; ++i) printk("%x ", a[i]);
}
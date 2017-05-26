#ifndef INCLUDE_FS
#define INCLUDE_FS

struct inode{
	int type;// D/F - R W - - - -；第一位标明目录0或文件1；E属性未实现
	int name_length;//文件名长度，紧跟在文件inode后面
	int next;//一个兄弟
	int child;//一个儿子
	int addr;//文件起始地址
	int size;//文件长度
};


#endif
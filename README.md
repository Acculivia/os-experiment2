# OS-experiment2

----

This time I'm trying to implement as many OS's features as I can.

Based on [hurlex's kernel](https://github.com/hurley25/hurlex-doc). I would thank him for making such a fantastic tutorial that allows me to find out the beauty to design an kernel.



Features I'm planning to add:

- [x] Keyboard interrupt: how to handle it.
- [x] Disk reading & writing: how to r/w disk without using `INT 13H` & switching between pmode & rmode.
- [ ] File system(virtual? or using the disk?), read & write from & to disk
- [ ] Basic shell, nasty dirty UI works
- [ ] (Maybe quite hard?) Figure out how `fork`, `exec` works
- [ ] Exec processes from file
- [ ] VGA programming is maybe too hard for me
- [ ] (To be continued…)



Problems & ideas I've found:

* Just for fun, how to make more than one disks to be a part of the virtual memory? By setting page maps? (BTW, also learnt that all virtual memories only contains volatile data)
* How to set up page maps for every processes, in order to make them having their own virtual space?


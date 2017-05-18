# OS-experiment2

----

This time I'm trying to learn & implement as many OS's features as I can.

Based on various resources, mostly and firstly [hurlex's kernel](https://github.com/hurley25/hurlex-doc). I would thank him for making such a fantastic tutorial that allows me to find out the beauty to design an kernel. (Though his docs are still too short for me to understand some important concepts XDD)

BTW, something that is quite not relevant to this project. I'm thinking that I can actually learn anything if I want, but it's just a (vital) matter of TIME………(just as if, P!=NP but PS=NPS)……. And I am starting to hold an aspect that no matter what I am learning, math or biology or finance or philosophy, no matter how different they seem, they are all the same……. there's no a better or a worse choice between them...

--------

Features I'm planning to add:

- [x] Keyboard interrupt: how to handle it.
- [x] Disk reading & writing: how to r/w disk without using `INT 13H` & switching between pmode & rmode.
- [ ] File system(virtual? or using the disk?), read & write from & to disk
- [ ] Basic shell, nasty dirty UI works
- [ ] (Maybe quite hard?) Figure out how `fork`, `exec` works
- [ ] Exec processes from file
- [ ] VGA programming, which is too tedious for me
- [ ] Maybe add a Lisp interpreter?
- [ ] (To be continued…)



Problems & ideas I've found:

* Just for fun, how to make more than one disks to be a part of the virtual memory? By setting page maps? (BTW, also learnt that all virtual memories only contains volatile data) ==> unsolved
* How to set up page maps for every processes, in order to make them having their own virtual space?  ==> pte, pgd, deeper understanding about concepts of virtual memory machinery
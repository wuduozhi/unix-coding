# unix-coding

这是一个关于 Unix/Linux 的仓库，同时也是自己了解与学习 Unix/Linux 操作系统平台的过程中的点滴记录。

这一切都源于极客时间的一门课程 `趣谈Linux操作系统` ，刘超老师通关部分源码与趣味性的方式来讲解 Linux 操作系统。自己跟老师的步伐学了十几节课程，但是感觉自己并没有完全吸收，似懂非懂。

![学习路径](<https://static001.geekbang.org/resource/image/bc/5b/bcf70b988e59522de732bc1b01b45a5b.jpeg>)

有这种感觉，是因为自己跳级了。对于学习，要要一步一步来，正如刘超老师上图总结的一样。自己当前正处在能正常使用 Linux ，与能在 Linux 上做一些开发，正处在节点 2 这里，现在直接大跃进去看源码，肯定一头雾水。

然后，自己就重新制定战略，决定重新捡起 c 语言，用 c 语言编程的方式，了解 Linux 操作系统，这个仓库也就诞生了。

对于与我处于同一节点的同志们，自己建议按如下步骤来学习：

## [Unix/Linux 编程实践教学](https://book.douban.com/subject/1219329/)

这本书一个很好的特点 `源码丰富`，光看源码就能学习到很多东西。这本书与其他书有很大的不同点：不死板的教原理，而是通过图片与代码的形式，带读者动手自己编程实现一些常用的 Linux 命令，如 `ls`,`pwd`,`who`,`cp`...这些基本的命令的实现，会涉及到操作系统的方方面面，文件系统、内存管理、进程、进程通信、输入输出设备、网络等。

可以说，看完这本书，把书中的例子实现一遍，对操作系统的理解会进一步加深的，对一些常用的 Linux 命令，更是知其然，更知其所以然。

## [Linux 高性能服务器编程](https://book.douban.com/subject/24722611/)

## [UNIX 网络编程 卷1](https://book.douban.com/subject/4859464/)

编译时必须加上静态链接库：-l 参数加上 libunp.a  去掉lib和后面的.a。最后得到参数-lunp

`gcc daytimetcpcli.c -o daytimetcpcli -l unp`

## APUE 源码编译

http://www.voidcn.com/article/p-vpolyqli-bmp.html

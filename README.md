# unix-coding
UNIX 编程实践

编译时必须加上静态链接库：-l 参数加上 libunp.a  去掉lib和后面的.a。最后得到参数-lunp

gcc daytimetcpcli.c -o daytimetcpcli -lunp 

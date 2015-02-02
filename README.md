### flash-policy-server

flashsocket 跨域访问时，首先需要获取跨域策略文件 crossdomain.xml, 然后根据跨域策略文件中的权限控制来确定是否进一步发起视频资源的请求。
如果跨域策略文件请求失败，将不会进一步发起视频资源的请求，这个项目实现一个简单的tcpserver，监听843端口的客户请求，并发送跨域策略文件给客户。

安装使用方法：
1. make  (编译 flash-policy-serv)
2. make install (安装flash-policy-serv)
3. nohup /usr/local/flash-policy-serv/bin/flash-policy-serv & (启动 flash-policy-serv)

注：服务器进程暂时没有daemonize，也没有服务化，进一步工作；

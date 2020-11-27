#ps -elf|grep tcpserver|grep unix_s|awk '{print $4}'|xargs kill -10
ps -elf|grep tcpserver|grep ep_pol|awk '{print $4}'|xargs kill -10

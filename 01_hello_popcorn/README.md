# 01 LKM Hello World 
## Commands

### Adding to Kernel
`sudo insmod mymodule.ko`

### Identifying in Kernel
`lsmod | grep mymodule`

### View Kernel Log
`dmesg | tail` 
- tail will show the last 10 messages by default
- use -n 5 to show last 5 messages
### Remove from Kernel
`sudo rmmod mymodule`

# Commands

## Adding to Kernel
`sudo insmod mymodule.ko`

## Identifying in Kernel
`lsmod | grep mymodule`

## View Kernel Log
`dmesg | tail` 
- tail will show the last 10 messages by default

## Remove from Kernel
`sudo rmmod mymodule`

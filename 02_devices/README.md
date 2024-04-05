# 02 Device Numbers and Files

## How to view devices?
- `ls /dev`
- Returns all the devices 

## How to view devices along with their `Major` and `Minor` numbers?
- `ls -al /dev`
- Returns all the devices with their additional information

## How to view what device numbers are available
- `cat /proc/devices`

## How to add device to `/dev`?
- `sudo mknod /dev/carameldevice c 30 0`
- c is for character
- 30 - Major, 0 - Minor

## How to give permissions to `/dev/carameldevice`?
- `sudo chmod 666 /dev/carameldevice`
- 666 grants read and write persmissions to everyone
## Extra information
### What is an inode?
- An inode is a file structure that stores information about any Linux file except its name and data
#### Why are they useful?
- Data is stored on the disk in fixed-size blocks
- If you save a file that exceeds the standard block, os will find the next available segment on which to store the rest of the file
- Over-time can get very confusing, that is where inode comes inode
#### What do they contain?
- inodes contain all metadata about the file, except for the name and data
- Contains
    - File size
    - Device on which file is stored
    - Users and group IDs associated with the file
    - Creation, read, and write timestamps
    - Location of the data
- They are independant of filenames, that means you can copy a single file and rename it, and have it point back to the same inodes
#### Drawbacks
- since blocks are still fixed-size, it is possible there is a file that exceeds the size of the inode
- to solve this, indirect pointers are used, where other inodes are indirectly pointed to, to fully encompass all the data

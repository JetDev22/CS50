- to compile a c file
```bash
make filename
```
- to run a compiled file
```bash
./filename
```
- Short change directory, this command changes your current directory to another. The short hand for your current directory is **"."** and for the parent directory is **".."**. If ever curious about the name of the current directory, type **"pwd"** which means present working directory.
```bash
cd <directory>
```
- go to parent directory
```bash
cd ..
```
- Short for remove, this command will delete the file after it asks you to confirm with yes or no. You can skip the confirmation with the -f flag. You cannot undo any delete. To delete a directory you have to use the  -r flag which stands for recursive
```bash
rm <file>
rm -f <file>
rm -r <directory>
```
- This command will create a folder / directory in your current directory
```bash
mkdir <directory>
```
- remove a folder / directory
```bash
rmdir
```
- Short for move, this command will allow you to effectively rename a file, moving it from source to destination.
```bash
mv <source> <destination>
```
- create a new file to code and open in vscode
```bash
code test.c
```
- short for list, this command will give you a readout of all the files and folders in your current directory
```bash
ls
```
- Short for copy, this command will allow you to create a duplicate of the file you specified as source, which it will save in destination. If you wish to copy an entire folder you have to use the -r flag which stand for recursive and tells cp to dive down into the directory and copy everything inside of it
```bash
cp <source> <destination>
cp -r <source directory> <destination>
```

## Screenshot of hw1

![alt text](https://github.com/jj535/CS288-F2020/blob/main/homework/hw1/HW1Screenshot_jj535.png)

### 1. Write a Bash script, count.sh, which builds a table of counters for the commands under /bin in alphabetical order. For example, there are 9 commands starting with "a" (a2p addftinfo addr2line apropos ar arch as ash awk) while there are 11 commands starting with "z" (zcat zcmp zdiff zegrep zfgrep zforce zgrep zless zmore znew zsoelim). Exclude commands starting with non-alphabets such as "[." Your script will print

```
a 9 
...
...
...
z 11
```
### The above list is a sample, just one example. You Linux distro can give you a totally different number of commands. Use loop and array to design and implement this script.

### 2. Write a Bash script, reverse.sh, which reverses the contents of a directory passed as a parameter. Assuming /my/dir contains "cache cron games lib log run tmp," your program "reverse.sh /my/dir" will return "tmp run log lib games cron cache." Use an array and two functions: main() and reverse(). You will manually manipulate the list as we did today. DO NOT use the built-in command sort -r.

### 3. Write a Bash script, filter.sh, which prints those files/directories that have the size greater than the average file size of the directory. Suppose for example that the directory /my/dir has five files/directories with size in parentheses " a (100) b (10) c (100) d (100) e (20)", your program "filter.sh /my/dir" will list "a c d" since the size of each of the three files/directories "a c d" is greater than the average file size of 66. Use three functions: main, average, and filter, where main calls average and filter, and average computes the average file size of a directory and filter filters out those that have less than the average. Use ls -l to get file size in bytes. Directories will be 4 KB, a page (be it diskblock or internal memory). Files will come in various size. Try not to use wc or du. Use of these defeats the purpose of learning various basic linux commands.

### 4. Write a Bash script, insert-sort.sh, which sorts a list of command line parameters in ascending order. For example, your command will look something like:
```
$ insert-sort.sh 7 2 3 9 -1 and type enter.
Your program will return: -1 2 3 7 9
```
### Use only basic commands and array. Do not use any built-in commands that sort array.

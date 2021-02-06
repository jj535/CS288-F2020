### Screenshot of output
![alt text](https://github.com/jj535/CS288-F2020/blob/main/homework/hw2/output_depth.png)
Depth first 
![alt text](https://github.com/jj535/CS288-F2020/blob/main/homework/hw2/output_breath.png)
Breath first
### Write a Linux Bash script, create.sh which creates a directory tree with depth d and breadth b in a programmable depth/breadth-first fashion, where depth-first or breadth-first can be crontrolled by a command line parameter. Depth refers to the level of the directory tree while breadth refers to the number of directories a directory may have. Use d and b between 3 and 5 inclusive for testing purposes. Your script must be able to handle any depth and breadth. Your command "create.sh 3 4 /home/cs288/hw2/tree depth" will create a tree with depth 3 and breath 4 at /home/cs288/hw2/tree-depth in depth-first while your command "create.sh 4 3 /home/cs288/hw2/tree breadth" will create a tree with depth 4 and breath 3 at /home/cs288/hw2/tree-breadth in breadth-first.
#### This program doesn't really create diretories. However creating the directory can be easily done with putting `mkdir PATH`. 

# get_next_line

### Description:
A function which returns a line read from a file descriptor, without the newline.
This function uses <i>a static pointer</i> to a list that stores file descriptors and text buffers associated with them. This allows you to get the specific next line from any existing file descriptor each time the function is called.

### Prototipe:
`int  get_next_line(int fd, char *line);`

### Usage:
This function is convenient to use in a loop:

```
while (get_next_line(fd, &line) > 0) {
  printf("%s\n", line);
  free(line);
}
printf("%s\n", line);
free(line);
```

### Return value:
The function returns
* 1 if the string was read successfully
* -1 if an error occurred
* 0 if EOF was reached.

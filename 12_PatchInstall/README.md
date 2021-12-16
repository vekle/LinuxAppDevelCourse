# Out-of-tree build and install
```shell
cmake -DCMAKE_INSTALL_PREFIX=[installation path] .. && DESTDIR=[destination path] make all install
```
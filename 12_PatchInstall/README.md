# Build and install in custom directory 
```shell
cd [build directory] && cmake -DCMAKE_INSTALL_PREFIX=[installation path] [source directory] && DESTDIR=[destination path] make all install
```
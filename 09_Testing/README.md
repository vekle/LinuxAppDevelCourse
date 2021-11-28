# Out-of-tree build and coverage check
```shell
mkdir build && cd build && cmake .. && make && make test && make ExperimentalCoverage && cd ..
```

# Clean
```shell
rm -rf build
```
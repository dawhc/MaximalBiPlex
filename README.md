# MaximalBiPlex
Maximal biplex enumeration algorithm $BPPivot$ & $BPBnB$


## Build
```bash
cmake . && make
```

## Run

- Command: 

```bash
bin/run <dataset> <q> <k>
```
- Example:

```bash
bin/run datas/opsahl_ucforum.txt 3 1
```

- How to choose algorithm:

> Comment out (or delete) the macro `#define WITH_PIVOTING ` in `src/biplex/biplex.cpp` to modify the algorithm from $BPPivot$ to $BPBnB$.


# MaximalBiPlex
Maximal biplex enumeration algorithm $BPPivot$ & $BPBnB$


## Build
```bash
cmake . && make
```

## Run

- Command: 

```bash
bin/run -d <dataset> -q <size> -k <k> [options]

usage: bin/run -d=string -q=int -k=int [options] ...
options:
  -d, --data                      dataset path (string)
  -q, --lb                        size lowerbound (int)
  -k, --key                       value of k (int)
  -n, --num                       number of result (unsigned long long [=18446744073709551615])
      --no-pivoting               disable pivoting (i.e. using algorithm BPBnB instead of BPPivot)
      --no-upperbound             disable upperbound pruning
      --no-core-reduction         disable core reduction
      --no-butterfly-reduction    disable butterfly reduction
      --no-ordering               disable ordering
  -h, --help                      print this message

```
- Example:

```bash
bin/run -d datas/opsahl_ucforum.txt -q 3 -k 1 # BPPivot
bin/run -d datas/opsahl_ucforum.txt -q 3 -k 1 -a BPBnB # BPBnBNU
bin/run -d datas/opsahl_ucforum.txt -q 3 -k 1 --no-butterfly-reduction # BPPivotC
bin/run -d datas/opsahl_ucforum.txt -q 3 -k 1 --no-ordering # BPPivotNO
```

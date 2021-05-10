# parallel-programming-mpi

## HowToUse
### コンパイル
```$ mpicc <cファイル名> -o <実行ファイル名>```

### 実行
```$ mpirun -np <プロセス数> ./<実行ファイル名>```

--oversubscribeオプション：予め定義されたスロット数よりプロセス数が多い場合につける

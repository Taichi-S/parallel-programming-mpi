# parallel-programming-mpi

## git
### clone
```$ git clone https://github.com/Taichi-S/parallel-programming-mpi.git```

## HowToUse
### コンパイル
```$ mpicc <cファイル名> -o <実行ファイル名>```

### 実行
```$ mpirun -np <プロセス数> ./<実行ファイル名>```

--oversubscribeオプション：予め定義されたスロット数よりプロセス数が多い場合につける

## ファイル説明
- hello.c
  - 「Hello MPI World」を指定されたプロセス数で実行

## 参考記事
一週間でなれる！スパコンプログラマ
https://kaityo256.github.io/sevendayshpc/
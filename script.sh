#!/bin/bash
dir=/home/ubuntu/exp_1/$1

ssh vm2 'script_vm_before.sh $1 && exit'

hadoop fs -rm -r /tmp/hadoop-yarn/staging/history/
mkdir -p $dir
cp /proc/net/dev $dir/start_netstat
cp /proc/diskstats $dir/start_diskstat

hive --hiveconf hive.execution.engine=mr -f sample-queries-tpcds/query$1.sql --database tpcds_text_db_1_50 2> $dir/query_mr_stderr.out 1> $dir/query_mr_stdout.out

cp /proc/net/dev $dir/end_netstat
cp /proc/diskstats $dir/end_diskstat

ssh vm2 'script_vm_after.sh $1 && exit'

sleep 2m
hadoop fs -copyToLocal /tmp/hadoop-yarn/staging/history/ $dir/
#!/bin/bash
dir=/home/ubuntu/exp_1/$1

hadoop fs -rm -r /tmp/hadoop-yarn/staging/history/
mkdir -p $dir
cp /proc/net/dev $dir/start_netstat
cp /proc/diskstats $dir/start_diskstat
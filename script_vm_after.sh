#!/bin/bash
dir=/home/ubuntu/exp_1/$1

cp /proc/net/dev $dir/end_netstat
cp /proc/diskstats $dir/end_diskstat
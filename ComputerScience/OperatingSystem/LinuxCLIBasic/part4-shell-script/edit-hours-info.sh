#!/bin/bash

usage(){
    echo "usage: $(basename $0) directory" >&2
}

# Check the argument is a directory
if [[ ! -d $1 ]]; then
    usage
    exit 1
fi

# Init array for hours : hours[i]=number of files edited at i hours
for i in {0..23}; do 
    hours[i]=0
done

# Collect data
files_edit_time=$(stat -c %y "$1"/* | cut -c 12-13)
for hour_str in $files_edit_time; do
    hour=${hour_str/#0}
    ((++hours[hour]))
    ((++count))
done

# Display data
echo -e "Hour\tFiles\tHour\tFiles"
echo -e "----\t-----\t----\t-----"
for hour in {0..11}; do
    next=$((hour+12))
    printf "$%02d\t%d\t%02d\t%d\n" $hour ${hours[hour]} $next ${hours[next]}
done
printf "\nTotal files = %d\n" $count
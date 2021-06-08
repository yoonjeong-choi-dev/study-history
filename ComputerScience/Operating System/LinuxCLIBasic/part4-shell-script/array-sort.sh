#!/bin/bash

sort_array(){
    arr=("$@")
    sorted=($(for i in "${arr[@]}"; do echo $i; done | sort))
    echo "Sorted array : ${sorted[@]}"
}

arr=(f e d c b a)
echo "Original Array: ${arr[@]}"
sorted=($(for i in "${arr[@]}"; do echo $i; done | sort))
echo "Sorted Array: ${sorted[@]}"


sort_array z f xa ab1 ab2
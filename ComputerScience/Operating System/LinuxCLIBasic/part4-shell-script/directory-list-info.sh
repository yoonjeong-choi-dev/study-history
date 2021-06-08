#!/bin/bash

while read attr links owner group size date time filename; do

    cat << EOF
Filename:   $filename
Size:       $size
Owner:      $owner
Gruop:      $group
Midified:   $date $time
Links:      $links
Attributes: $attr
EOF
echo " "
done < <(ls -l | tail -n +2)
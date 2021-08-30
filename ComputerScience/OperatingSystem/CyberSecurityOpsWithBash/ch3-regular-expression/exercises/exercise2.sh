#!/bin/bash

TEXT=$1

egrep '([0-9]+).*=.*\1' $TEXT
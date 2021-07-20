#!/bin/bash

kubectl create deployment in-hname-pod --image=sysnet4admin/echo-hname
kubectl create deployment in-ip-pod --image=sysnet4admin/echo-ip
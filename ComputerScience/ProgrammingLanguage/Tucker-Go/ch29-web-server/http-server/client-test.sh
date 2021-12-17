#!/bin/bash

echo "GET /"
curl "localhost:8080"
echo ""; echo ""

echo "GET /greet?name=YJ&id=777"
curl "localhost:8080/greet?name=YJ&id=777"
echo ""; echo ""

echo "GET /greet"
curl "localhost:8080/greet"
echo ""; echo ""

echo "GET /student"
curl "localhost:8080/student"
echo ""; echo ""
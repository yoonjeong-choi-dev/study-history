#!/bin/bash

export CLASSPATH=$CLASSPATH:$(pwd)/classes

# single server
javac -encoding UTF-8 -d classes src/server/CalculatorServer.java

# client
javac -encoding UTF-8 -d classes src/client/CalculatorAgent.java
javac -encoding UTF-8 -d classes src/client/CalculatorFrame.java

# multi server
javac -encoding UTF-8 -d classes src/multiserver/CalculatorWorker.java
javac -encoding UTF-8 -d classes src/multiserver/CalculatorServer.java
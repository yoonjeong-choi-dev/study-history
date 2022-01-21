#!/bin/bash

echo "Run extends example"
npx babel src/extends-example/simple-code.js

echo "";

echo "Run env example : dev"
npx babel src/env-example/simple-code.js

echo "";

echo "Run env example : production"
NODE_ENV=production npx babel src/env-example/simple-code.js

echo "";

echo "Run overrides example : 화살표 함수 add 확인"
NODE_ENV=production npx babel src/overrides-example/

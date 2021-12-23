#!/bin/bash

# build-dev-image로 빌드한 이미지에 대해서 컨테이너 실행
# -v 옵션 1 : 컨테이너 내부의 패키지 관련 디렉터리 참조(Dockerfile.dev 참고)
# -v 옵션 2 : 패키지를 제외한 파일들은 로컬 파일 참조ㅓ
# -it : 리액트 앱에 대한 컨테이너 실행 시 필수 옵션
docker run -it --rm -p 3000:3000 -v /yj-react-app/node_modules -v $(pwd):/yj-react-app docker-ci/react-app
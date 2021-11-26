
# 멀티 스테이지 빌드
# Step 1 : 어플리케이션 빌드
FROM golang AS build

ENV  BUILD_DIR /tmp/app-image
WORKDIR ${BUILD_DIR}

ADD . .

RUN go mod tidy \
    && go get -u -d -v ./...

RUN CGO_ENABLED=0 go build -o /bin/grpc-productinfo-server


# 빌드된 바이너리 파일로 컨테이너 생성
FROM scratch
COPY --from=build /bin/grpc-productinfo-server /bin/grpc-productinfo-server


ENTRYPOINT ["/bin/grpc-productinfo-server"]
EXPOSE 50051
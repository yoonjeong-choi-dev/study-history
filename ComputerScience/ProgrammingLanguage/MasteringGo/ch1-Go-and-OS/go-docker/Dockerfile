FROM golang:alpine

RUN mkdir /files
COPY go-docker.go /files
WORKDIR /files

RUN go build -o /files/go-docker go-docker.go
ENTRYPOINT [ "/files/go-docker" ]

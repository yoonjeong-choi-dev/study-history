provider "aws" {
  region = "ap-northeast-2"
}

# EC2 인스턴스 정의
resource "aws_instance" "example" {
  instance_type = "t2.micro"
  availability_zone = "ap-northeast-2a"
  ami = "ami-0ba5cd124d7a79612"

  # 보안 그룹 연결
  vpc_security_group_ids = [aws_security_group.instance.id]

  # EC2 인스턴스 시작 시, 수행하는 스크립트 정의
  user_data = <<-EOF
              #!/bin/bash
              echo "Hello, YJ!" > index.html
              nohup busybox httpd -f -p ${var.server_port} &
              EOF

  # EC2 태그 정의
  tags = {
    "Name" = "my-first-terraform"
  }
}

# 보안 그룹 정의(웹서버용) : var.server_port포트로 오는 모든 TCP 허용
resource "aws_security_group" "instance" {
  name = var.security_group_name

  ingress {
    from_port = var.server_port
    to_port = var.server_port
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    "Name" = "simple-web-sg"
  }
  
}
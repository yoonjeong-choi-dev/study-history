provider "aws" {
  region = "ap-northeast-2"
}

# ASG(Auto Scaling Group) 시작 구성 정의
# ASG에서 각 EC2 인스턴스 자체에 대한 정의
resource "aws_launch_configuration" "example" {
  image_id = "ami-0ba5cd124d7a79612"
  instance_type = "t2.micro"
  #availability_zone = "ap-northeast-2a"

  # 보안 그룹 연결
  security_groups = [aws_security_group.instance.id]

  # EC2 인스턴스 시작 시, 수행하는 스크립트 정의
  user_data = <<-EOF
              #!/bin/bash
              echo "Hello, YJ!" > index.html
              nohup busybox httpd -f -p ${var.server_port} &
              EOF

  # ASG에서 시작 구성을 사용할 때 필요
  # : 리소스 교체 시, 먼저 교체 리소스를 생성하고 그 후에 교체될 리소스를 삭제
  lifecycle {
    create_before_destroy = true
  }
}

# 보안 그룹 정의(EC2 웹서버용) : var.server_port포트로 오는 모든 TCP 허용
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

# ASG 정의
resource "aws_autoscaling_group" "example" {
  # 시작 구정 정보 정의
  launch_configuration = aws_launch_configuration.example.name

  # ASG에서 어느 VPC의 서브넷에 EC2 인스턴스를 배포하는지 정의
  vpc_zone_identifier = data.aws_subnet_ids.default.ids

  # 헬스체크 타입을 기본 EC2에서 ELB로 변경
  # ASG가 대상 그룹의 상태 확인을 통해 해당 인스턴스의 정상 여부 확인
  target_group_arns = [aws_lb_target_group.asg.arn]
  health_check_type = "ELB"

  # EC2 인스턴스들 설정
  min_size = 2
  max_size = 10

  tag {
    key = "Name"
    value = "terraform-asg-example"
    propagate_at_launch = true
  }
}

# ASG에 적용할 VPC와 서브넷 id를 가져오기 위한 데이터 소스 정의
data "aws_vpc" "default" {
  default = true
}

data "aws_subnet_ids" "default" {
  vpc_id = data.aws_vpc.default.id
}


# 사용자에게 노출시켜야 할 로드벨런서 정의
# : ASG에서 생성된 EC2 인스턴스들은 로드밸런서에 의해 사용자에게 노출
resource "aws_lb" "example" {
  name = "terraform-asg-example"
  load_balancer_type = "application"
  subnets = data.aws_subnet_ids.default.ids

  # 보안그룹 연결
  security_groups = [aws_security_group.alb.id]
}

# 로드밸런서 구성 1
# 로드밸런서 리스너 정의 : 포트 및 프로토콜
resource "aws_lb_listener" "http" {
  load_balancer_arn = aws_lb.example.arn
  port = 80
  protocol = "HTTP"

  # 404 기본 페이지 정의
  default_action {
    type = "fixed-response"

    fixed_response {
      content_type = "text/plain"
      message_body = "404: page not found"
      status_code = 404
    }
  }
}

# 로드밸런서 구성 2
# 리스너 규칙 : 모든 경로에 대한 요청을 대상 그룹으로 보내는 규칙
resource "aws_lb_listener_rule" "asg" {
  listener_arn = aws_lb_listener.http.arn
  priority = 100

  condition {
    path_pattern {
      values = ["*"]
    }
  }

  action {
    type = "forward"
    target_group_arn = aws_lb_target_group.asg.arn
  }
}

# 로드밸런서 구성 3
# 대상 그룹 정의 : 요청을 받는 하나 이상의 서버
# => 서버의 상태를 확인하여 정상인 서버에만 트래픽 전송
resource "aws_lb_target_group" "asg" {
  name = "terraform-asg-example"

  port = var.server_port
  protocol = "HTTP"

  vpc_id = data.aws_vpc.default.id

  health_check {
    path = "/"
    protocol = "HTTP"
    matcher = "200"
    interval = 15
    timeout = 3
    healthy_threshold = 2
    unhealthy_threshold = 2
  }
}



# 로드밸런서 ALB를 위한 보안 그룹 정의
resource "aws_security_group" "alb" {
  name = "terraform-alb-sg"

  # HTTP 인바운드 트래픽 허용 : HTTP를 통해 로드밸런서에 접속 가능
  ingress {
    from_port = 80
    to_port = 80
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  # 모둔 아웃바운드 트래픽 허ㅓ용 => 헬스 체크 수행 가능하도록
  egress {
    from_port = 0
    to_port = 0
    protocol = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    "Name" = "terraform-alb-sg"
  }
}
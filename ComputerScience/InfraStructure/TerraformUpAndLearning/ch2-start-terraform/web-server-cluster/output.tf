# 테라폼 출력 데이터 정의 : 로드밸런서 dns 출력
# terraform output 명령어를 이용하여 확인 가능

output "alb_dns_name" {
  value = aws_lb.example.dns_name
  description = "The domain name for the load balancer"
}


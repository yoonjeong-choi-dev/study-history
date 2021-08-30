# 테라폼 출력 데이터 정의 : 서버 IP
# terraform output 명령어를 이용하여 확인 가능

output "public_ip" {
  value = aws_instance.example.public_ip
  description = "The public IP address for the simple web server"
}
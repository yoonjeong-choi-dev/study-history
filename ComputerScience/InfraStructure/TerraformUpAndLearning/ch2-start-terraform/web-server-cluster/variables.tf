# 웹 서버 네트워크 관련 변수들

variable "server_port" {
  description = "The port the server will use for HTTP requests"
  type        = number
  default     = 8080
}

variable "security_group_name" {
  description = "The name of the security group for EC2 instance"
  type        = string
  default     = "terraform-webserver-sg"
}
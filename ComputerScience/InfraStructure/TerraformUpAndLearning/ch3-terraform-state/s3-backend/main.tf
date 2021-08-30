provider "aws" {
  region = "ap-northeast-2"
}

# 테라폼 상태 저장을 위한 S3 버킷 정의
resource "aws_s3_bucket" "terraform_state" {
  # 버킷 이름 정의
  bucket = "yjchoi-terraform-state"

  # 실수로 버킷이 삭제되는 것 방지
  lifecycle {
    prevent_destroy = true
  }

  # 상태 파일의 버전 관리 활성화
  versioning {
    enabled = true
  }

  # 서버 측 암호화 활성화 : 상태 파일 암호화
  server_side_encryption_configuration {
    rule {
      apply_server_side_encryption_by_default {
        sse_algorithm = "AES256"
      }
    }
  }
}

# 잠금 기능을 위한 DynamoDB 설정
resource "aws_dynamodb_table" "terraform_locks" {
  name = "terrform-state-locks"
  billing_mode = "PAY_PER_REQUEST"

  # 테라폼에서 DynamoDB를 잠금에 사용하려면 해쉬 키를 LockID로 설정해야 함
  hash_key = "LockID"

  attribute {
    name = "LockID"
    type = "S"
  }
}

# 테라폼 백엔드 구성
# : 우선 위 코드에 대해 init 실행 후 해당 코드를 작성하고 init을 다시 실행해야 함.
# i.e S3 및 DynamoDB 설정이 끝난 후에 설정 가능
# terraform {
#   backend "s3" {
#     # s3 버킷 정보 입력
#     bucket = "yjchoi-terraform-state"
#     key = "global/s3/terraform.tfstate"
#     region = "ap-northeast-2"

#     # dynamoDB 정보 입력
#     dynamodb_table = "terrform-state-locks"
#     encrypt = true
#   }
# }
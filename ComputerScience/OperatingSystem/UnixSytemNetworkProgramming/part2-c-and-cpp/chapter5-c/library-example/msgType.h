#define REQUEST 1
#define RESPONSE 2

typedef struct 
{
  int type;
  char data[10];
} RequestType;

typedef struct
{
  int isDone;
  char data[20];
} ResponseType;

// 요청이나 응답을 저장하는 메시지 구조체
typedef struct 
{
  unsigned int messageType;

  // messageType에 따라 공용체를 이용하여 데이터 저장
  union 
  {
    RequestType request;
    ResponseType response;
  } uType;
  
} MessageType;
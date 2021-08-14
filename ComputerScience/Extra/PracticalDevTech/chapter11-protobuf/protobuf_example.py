import simple_message_pb2
import uuid


def create_protobuf_msg():
    # 인터페이스 코드를 통해 객체 생성
    protobuf_msg = simple_message_pb2.SimpleMessage()

    # 기본 필드
    protobuf_msg.name = u"문자열"
    protobuf_msg.num64 = 930713
    protobuf_msg.float64 = 9.30713
    protobuf_msg.uuid = uuid.uuid4().bytes

    # 이넘 타입
    protobuf_msg.type = simple_message_pb2.SimpleMessage.Ping

    # 리스트
    protobuf_msg.num64_list.append(1)
    protobuf_msg.num64_list.append(2)

    protobuf_msg.name_list.append(u"one")
    protobuf_msg.name_list.append(u"two")

    # 맵
    protobuf_msg.map_field["key1"] = u"value1"
    protobuf_msg.map_field["key2"] = u"value2"

    # 내부 객체
    protobuf_msg.another_msg.name = u"내부 문자열"
    protobuf_msg.another_msg.num64 = 123

    # 내부 객체 리스트
    for i in range(5):
        inner_msg = simple_message_pb2.AnotherMessage()
        inner_msg.name = u"내부 문자열{}".format(i)
        inner_msg.num64 = i
        protobuf_msg.another_msg2.append(inner_msg)

    return protobuf_msg


def print_protobuf_msg(protobuf_msg):
    print("==============================================================")
    print("name={}".format(protobuf_msg.name))
    print("num64={}".format(protobuf_msg.num64))
    print("float64={}".format(protobuf_msg.float64))
    print("uuid={}".format(str(uuid.UUID(bytes=protobuf_msg.uuid))))

    idx = 0
    for num64 in protobuf_msg.num64_list:
        print("num64_list[{}]={}".format(idx, num64))
        idx += 1

    idx = 0
    for name in protobuf_msg.name_list:
        print("name_list[{}]={}".format(idx, name))
        idx += 1

    print("type={}".format(protobuf_msg.type))

    for key in protobuf_msg.map_field:
        print("map_field[{}]={}".format(key, protobuf_msg.map_field[key]))

    print("another_msg.name={}".format(protobuf_msg.another_msg.name))
    print("another_msg.num64={}".format(protobuf_msg.another_msg.num64))

    idx = 0
    for msg2 in protobuf_msg.another_msg2:
        print("another_msg2[{}].name={}, num64={}".format(idx, msg2.name, msg2.num64))
        idx += 1

    print("==============================================================")


def convert_to_text(protobuf_msg):
    from google.protobuf import text_format
    return text_format.MessageToString(protobuf_msg, as_utf8=True)


def convert_to_json(protobuf_msg):
    from google.protobuf import json_format
    return json_format.MessageToJson(protobuf_msg)


if __name__ == "__main__":
    msg = create_protobuf_msg()
    print_protobuf_msg(msg)

    plain_text = convert_to_text(msg)
    print("==============================================================")
    print("Plain Text")
    print(plain_text)
    print("==============================================================")

    print("==============================================================")
    import json
    msg_json = convert_to_json(msg)
    print("Json format")
    print(json.loads(msg_json))
    print("==============================================================")


import socket
import time

from io import BytesIO
from random import randint

from ecc.block import Block
from ecc.utils import (
    hash256,
    encode_varint,
    int_to_little_endian,
    little_endian_to_int,
    read_varint,
)


NETWORK_MAGIC = b'\xf9\xbe\xb4\xd9'
TESTNET_NETWORK_MAGIC = b'\x0b\x11\x09\x07'


class NetworkEnvelope:
    """
    네트워크 메시지
    - 노드와 노드가 서로 교환하는 통신 패킷

    네트워크 메시지 구성 요소
    - 매직 바이트(바이트)
        - 첫 4바이트는 항상 동일하게 매직 바이트로 부여
        - 간헐적으로 끊어지는 비동기 네트워크 통신 프로그래밍에서 일반적으로 사용
          => 재접속을 위해 신호의 시작점을 알아내는데 유용
        - 네트워크마다 부여되는 번호가 다름
          => 네트워크 식별 가능
    - 커맨드 필드(바이트)
        - 12바이트로 구성
        - 페이로드가 어떤 정보인지 알려줌
        - 사람이 읽을 수 있는 텍스트를 ascii형식으로 저장하며, 빈 공간은 0x00로 채운다
    - 페이로드 길이(바이트)
        - 페이로드의 길이가 가변이기 때문에 필요
        - 4바이트 리틀엔디언으로 구성
    - 체크섬 필드(바이트)
        - 페이로드의 hash256 해시값의 첫 4바이트
        - 에러 탐지 기능으로만 사용
        - cf) 일반적인 네트워크 체크섬은 오류 정정 기능을 포함하여 설계
            - 오류 정정 기능 : 메시지의 내용이 전 송 중 오류가 발생하면 이를 복구할 수 있는 기능
    - 페이로드 필드
    """

    def __init__(self, command, payload, testnet=False):
        self.command = command
        self.payload = payload
        if testnet:
            self.magic = TESTNET_NETWORK_MAGIC
        else:
            self.magic = NETWORK_MAGIC

    def __repr__(self):
        return "{} : {}".format(
            self.command.decode("ascii"),
            self.payload.hex()
        )

    @classmethod
    def parse(cls, stream, testnet=False):
        # 매직 넘버 : 4바이트
        magic = stream.read(4)

        # 올바른 스트림인지 확인
        if magic == b"":
            raise RuntimeError("Connection Reset")

        if testnet:
            expected_magic = TESTNET_NETWORK_MAGIC
        else:
            expected_magic = NETWORK_MAGIC
        if magic != expected_magic:
            raise RuntimeError("magic is not right {} (expected : {}".format(magic, expected_magic))

        # 커맨드 필드 : 12바이트(빈공간 0x00포함)
        command = stream.read(12)
        command = command.strip(b"\x00")

        # 페이로드 길이 : 4바이트 리틀엔디언
        payload_length = little_endian_to_int(stream.read(4))

        # 체크섬 필드 : 4바이트
        checksum = stream.read(4)

        # 페이로드 필드
        payload = stream.read(payload_length)

        # 체크섬을 통한 에러 확인
        payload_checksum = hash256(payload)[:4]
        if payload_checksum != checksum:
            raise RuntimeError("checksum error")

        return cls(command, payload, testnet)

    def serialize(self):
        # 매직 넘버 : 4바이트
        ret = self.magic

        # 커맨드 필드 : 12바이트(빈공간 0x00포함)
        ret += self.command
        ret += b"\x00" * (12 - len(self.command))

        # 페이로드 길이 : 4바이트 리틀엔디언
        ret += int_to_little_endian(len(self.payload), 4)

        # 체크섬 필드 : 4바이트
        ret+= hash256(self.payload)[:4]

        # 페이로드 필드
        ret += self.payload

        return ret

    def stream(self):
        """
        페이로드를 스트림 객체로 만든다
        :return: 페이로드의 스트림 객체
        """
        return BytesIO(self.payload)

def exercise1():
    msg = bytes.fromhex('f9beb4d976657261636b000000000000000000005df6e0e2')
    stream = BytesIO(msg)
    envelope = NetworkEnvelope.parse(stream)

    command_ans = b"verack"
    payload_ans = b""

    print("parse command : {}".format(envelope.command == command_ans))
    print("parse payload : {}".format(envelope.payload == payload_ans))

def exercise2():
    message_hex = 'f9beb4d976657261636b000000000000000000005df6e0e2'
    message = bytes.fromhex(message_hex)
    magic = message[:4]

    if magic == NETWORK_MAGIC:
        print("main net")
    elif magic == TESTNET_NETWORK_MAGIC:
        print("test net")
    else:
        print("I don't know")

def exercise3():
    messages = [
        bytes.fromhex('f9beb4d976657261636b000000000000000000005df6e0e2'),
        bytes.fromhex(
            'f9beb4d976657273696f6e0000000000650000005f1a69d2721101000100000000000000bc8f5e5400000000010000000000000000000000000000000000ffffc61b6409208d010000000000000000000000000000000000ffffcb0071c0208d128035cbc97953f80f2f5361746f7368693a302e392e332fcf05050001')
    ]

    for msg in messages:
        stream = BytesIO(msg)
        envelope = NetworkEnvelope.parse(stream)
        print("serialized : {}".format(msg == envelope.serialize()))


class VersionMessage:
    """
    버전 커맨드에 대한 파싱
    - 네트워크 메시지의 커맨드 필드가 version 커맨드인 경우, 페이로드 내용 표현하는 클래스
    - 총 5개의 필드로 구성(순서 중요)
        - 프로토콜 버전
        - 서비스 정보
        - 타임스탬프
        - 수신자/송신자 정보
        - 기타 정보

    프로토콜 버전
    - 4바이트 리틀엔디언
    - 프로토콜에 따라서 통신 가능한 메시지가 제한

    서비스 정보
    - 8바이트 리틀엔디언
    - 수신자가 보내는 서비스 정보
    - 연결된 노드 사이에 사용 가능한 서비스 정보

    타임스탬프
    - 8바이트 리틀엔디언 정수
    - 유닉스 타임스탬프 필드

    수신자receiver) 및 송신자(sender) 정보
    - 서비스 정보
        - 위 서비스 정보와 같은 형식
    - IP 주소
        - 16바이트
        - IPv4인 경우, 첫 12바이트는 IPv6에 맞추고, 실질적인 주소는 뒤 4바이트
    - 포트 정보
        - 2바이트 빅엔디언 정수
        - 메인넷 디폴트는  8333, 빅엔디언으로 0x208d

    기타 정보
    - 논스
        - 8바이트
        - 노드가 어떤노드와 연결되었을 때, 의미 없는 자신과의 연결을 식별하기 위해 사용
        - 블록 헤더의 논스와 다른 용도
    - 사용자 에이전트
        - 가변 필드로 길이 정보가 포함
        - 실생 중인 소프트웨어 관한 정보
    - 높이
        - 4바이트 리틀엔디언
        - 메시지를 보내는 노드가 가장 최근에 동기화한 블록
    - 릴레이(Optional flag for replay)
        - 2비트
        - 블룸 필터와 관계(12장)
        - 리플레이인 경우 01비트, 아닌경우 00비트
    """
    command = b"version"

    def __init__(self, version=70015, services=0, timestamp=None,
                 receiver_services=0,
                 receiver_ip=b'\x00\x00\x00\x00', receiver_port=8333,
                 sender_services=0,
                 sender_ip=b'\x00\x00\x00\x00', sender_port=8333,
                 nonce=None, user_agent=b'/programmingbitcoin:0.1/',
                 latest_block=0, relay=False):

        self.version = version
        self.services = services
        if timestamp is None:
            self.timestamp = int(time.time())
        else:
            self.timestamp = timestamp

        self.receiver_services = receiver_services
        self.receiver_ip = receiver_ip
        self.receiver_port = receiver_port

        self.sender_services = sender_services
        self.sender_ip = sender_ip
        self.sender_port = sender_port

        if nonce is None:
            self.nonce = int_to_little_endian(randint(0, 2 ** 64), 8)
        else:
            self.nonce = nonce

        self.user_agent = user_agent
        self.latest_block = latest_block
        self.relay = relay

    def serialize(self):
        # 프로토콜 버전 : 4바이트 리틀엔디언
        ret = int_to_little_endian(self.version, 4)
        # 서비스 정보 : 8바이트 리틀엔디언
        ret += int_to_little_endian(self.services, 8)
        # 타임스탬프 : 8바이트 리틀엔디언
        ret += int_to_little_endian(self.timestamp, 8)
        # 수신자 서비스 정보 : 8바이트 리틀엔디언
        ret += int_to_little_endian(self.receiver_services, 8)
        # 수신자 IP : 16바이트 (첫 12바이트는 IPv6 형식)
        ret += b'\x00' * 10 + b'\xff\xff' + self.receiver_ip
        # 수신자 포트 정보 : 2바이트 빅엔디언
        ret += self.receiver_port.to_bytes(2, "big")
        # 송신자 서비스 정보 : 8바이트 리틀엔디언
        ret += int_to_little_endian(self.sender_services, 8)
        # 송신자 IP : 16바이트 (첫 12바이트는 IPv6 형식)
        ret += b'\x00' * 10 + b'\xff\xff' + self.sender_ip
        # 송신자 포트 정보 : 2바이트 빅엔디언
        ret += self.sender_port.to_bytes(2, "big")
        # 논스 : 8바이트
        ret += self.nonce
        # 사용자 에이전트 : 가변필드
        ret += encode_varint(len(self.user_agent))
        ret += self.user_agent
        # 높이 : 4바이트 리틀엔디언
        ret += int_to_little_endian(self.latest_block, 4)
        # 릴레이 : 2비트
        if self.relay:
            ret +=  b"\x01"
        else:
            ret += b"\x00"

        return ret

    @classmethod
    def parse(cls, stream):
        """
        # 프로토콜 버전 : 4바이트 리틀엔디언
        version = little_endian_to_int(stream.read(4))
        # 서비스 정보 : 8바이트 리틀엔디언
        service = little_endian_to_int(stream.read(8))
        # 타임스탬프 : 8바이트 리틀엔디언
        timestamp = little_endian_to_int(stream.read(8))
        # 수신자 서비스 정보 : 8바이트 리틀엔디언
        receiver_services = little_endian_to_int(stream.read(8))
        # 수신자 IP : 16바이트 (첫 12바이트는 IPv6 형식)
        stream.read(12)
        receiver_ip = stream.read(4)
        # 수신자 포트 정보 : 2바이트 빅엔디언
        ret += self.receiver_port.to_bytes(2, "big")
        # 송신자 서비스 정보 : 8바이트 리틀엔디언
        sender_services = little_endian_to_int(stream.read(8))
        # 송신자 IP : 16바이트 (첫 12바이트는 IPv6 형식)
        stream.read(12)
        sender_ip = stream.read(4)
        # 송신자 포트 정보 : 2바이트 빅엔디언
        ret += self.sender_port.to_bytes(2, "big")
        # 논스 : 8바이트
        nonce = stream.read(8)
        # 사용자 에이전트 : 가변필드
        ret += encode_varint(len(self.user_agent))
        ret += self.user_agent
        # 높이 : 4바이트 리틀엔디언
        ret += int_to_little_endian(self.latest_block, 4)
        # 릴레이 : 2비트
        relay_field = stream.read(2)
        if self.relay:
            ret += b"\x01"
        else:
            ret += b"\x00"
        """


        return cls()


def exercise4():
    v = VersionMessage(timestamp=0, nonce=b'\x00' * 8)
    serialized = v.serialize()

    ans_hex = '7f11010000000000000000000000000000000000000000000000000000000000000000000000ffff00000000208d000000000000000000000000000000000000ffff00000000208d0000000000000000182f70726f6772616d6d696e67626974636f696e3a302e312f0000000000'

    print("serialized : {}".format(serialized.hex() == ans_hex))

def example1():
    print("Network Test")

    # https://bitnodes.io/nodes/ 에서 호스트랑 포트번호 지정
    host = "199.182.184.204"
    port = 8333

    my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    my_socket.connect((host, port))

    stream = my_socket.makefile("rb", None)
    version = VersionMessage()
    envelope = NetworkEnvelope(version.command, version.serialize())
    my_socket.sendall(envelope.serialize())

    while True:
        new_msg = NetworkEnvelope.parse(stream)
        print(new_msg)



class VerAckMessage:
    """
    VerAck 커맨드에 대한 파싱
    - 네트워크 메시지의 커맨드 필드가 VerAck 커맨드인 경우, 페이로드 내용 표현하는 클래스
    - 네트워크 핸드셰이크 과정에서 특정 데이터를 수신 받았을 때, 상대방에게 수신받았음을 알리는 용도
    """
    command = b'verack'

    def __init__(self):
        pass

    @classmethod
    def parse(cls, stream):
        return cls()

    def serialize(self):
        return b""


class PingMessage:
    command = b'ping'

    def __init__(self, nonce):
        self.nonce = nonce

    @classmethod
    def parse(cls, s):
        nonce = s.read(8)
        return cls(nonce)

    def serialize(self):
        return self.nonce


class PongMessage:
    command = b'pong'

    def __init__(self, nonce):
        self.nonce = nonce

    @classmethod
    def parse(cls, s):
        nonce = s.read(8)
        return cls(nonce)

    def serialize(self):
        return self.nonce


class SimpleNode:
    """
    특정 노드와 통신하는 클래스
    - 생성자에서 받은 host 및 port를 대상 노드로 소켓을 생성
    - 대상 노드와 통신을 하면서 네트워크 메시지 송수신
        - 편의를 위해 동기 네트워크 프로그래밍
    """

    def __init__(self, host, port=None, testnet=False, logging=False):
        if port is None:
            if testnet:
                port = 18333
            else:
                port = 8333

        self.testnet = testnet
        self.logging = logging

        # 소켓 생성 및 연결
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((host, port))
        self.stream = self.socket.makefile("rb", None)

    def handshake(self):
        """
        네트워크 핸드셰이크
        - 노드 사이에 통신 링크를 처음 수립하는 과정
            - 해당 객체가 핸드셰이크를 신청함
            - 송신자
        - 과정
            - Step 1 : 송신자는 수신자에게 version 메시지 전송
            - Step 2 : 수신자는 version 메시지를 수신 받은 경우 다음 메시지들을 전송
                - 송신자가 제대로 전송했다는 것을 알리는 verack 메시지
                - 자신의 버전 정보인 version 메시지
            - Step 3 : 송신자는 수신자가 전송한 verack 및 version 메시지를 수신 받은 경우 verack 전송
            - Step 4 : 수신자는 verack 메시지를 수신받고 링크 형성
        :return: None
        """
        # Step 1 : 수신자에게 버전 메시지 전송
        version = VersionMessage()
        self.send(version)

        # Step 3 : 수신자에게서 verack 메시지를 받을 때까지 기다린다
        self.wait_for(VerAckMessage)

        if self.logging:
            print("handshaking success!")


    def send(self, message):
        """
        메시지를 소켓을 통해 연결된 노드로 전송
        :param message: *Message 메시지 객체
        :return: None
        """
        # message를 담고 있는 네트워크 메시지 생성
        envelope = NetworkEnvelope(
            message.command, message.serialize(), testnet=self.testnet
        )

        if self.logging:
            print("sending : {}".format(envelope.command.decode("ascii")))

        # message 전송
        self.socket.sendall(envelope.serialize())

    def read(self):
        """
        소켓을 통해 받은 메시지를 읽음
        :return: 읽은 메시지가 담긴 NetworkEnvelope 객체
        """
        # 소켓 스트림을 읽어 네트워크 메시지 생성
        envelope = NetworkEnvelope.parse(self.stream, testnet=self.testnet)

        if self.logging:
            print("receiving : {}".format(envelope.command.decode("ascii")))

        return envelope

    def wait_for(self, *message_classes):
        """
        동기적으로 네트워크 통신을 하기 위한 메서드
        - message_classes에 포함된 메시지 중 하나를 수신받을 때까지 기다린다
        - 수신받으면 파싱 결과를 반환
        - version이나 ping 메시지의 경우, 그에 따른 응답 메시지도 전송
            - 핸드셰이크 과정
        :param message_classes: 수신받고 싶은 메시지 클래스들
        :return: 수신받은 메시지 객체
         """
        command = None
        command_to_class = {m.command: m for m in message_classes}

        if self.logging:
            print("wait_for... : {}".format(command_to_class.keys()))

        while command not in command_to_class.keys():
            envelope = self.read()
            command = envelope.command

            # version이나 ping 메시지의 경우, 그에 따른 응답 메시지도 전송
            if command == VersionMessage.command:
                self.send(VerAckMessage())
            elif command == PingMessage.command:
                self.send(PingMessage(envelope.payload))

        return command_to_class[command].parse(envelope.stream())



def example2():
    host = "141.226.161.188"
    port = 8333

    node = SimpleNode('testnet.programmingbitcoin.com', testnet=True,logging=True)
    version = VersionMessage()
    node.send(version)

    verack_received = False
    version_received = False

    while not version_received or not version_received:
        message = node.wait_for(VerAckMessage, VersionMessage)
        if message.command == VerAckMessage.command:
            verack_received = True
        else:
            version_received = True

    print("Success!")


def exercise5():
    node = SimpleNode('testnet.programmingbitcoin.com', testnet=True, logging=True)
    node.handshake()


class GetHeadersMessage:
    """
    블록 헤더를 요청하는 커맨드
    - 연결된 상대 노드에게 블록 헤더를 요청
    - 처음 네트워크에 연결되고 입수해야하는 가장 중요한 데이터
    - 구성 요소
        - 프로토콜 버전 : 4바이트 리틀엔디언
        - 블록 헤더 갯수
            - 시작 블록 헤더의 개수
            - 가변 정수 형식
        - 시작 블록 헤더
            - 리틀엔디언
        - 마지막 블록 헤더
            - 리틀엔디언
            - 00000..00 인 경우, 상대 노드에게 최대한 많은 블록 헤더를 전송하라는 의미
    """
    command = b'getheaders'

    def __init__(self, version=70015, num_hashes=1, start_block=None, end_block=None):
        self.version = version
        self.num_hashes = num_hashes

        if start_block is None:
            raise RuntimeError("a start block is required")
        self.start_block = start_block

        if end_block is None:
            # 마지막 블록헤더가 주어지지 않은 경우, 최대한 많은 블록 헤더를 요청청
            self.end_block = b"\x00" *32
        else:
            self.end_block = end_block

    def serialize(self):
        # 프로토컬 버전 : 4바이트 리틀엔디언
        ret = int_to_little_endian(self.version, 4)

        # 블록 헤더 개수 : 가변 정수
        ret += encode_varint(self.num_hashes)

        # 시작 블록 : 리틀엔디언
        ret += self.start_block[::-1]

        # 마지막 블록 : 리틀엔디언
        ret += self.end_block[::-1]

        return ret


def exercise6():
    block_hex = '0000000000000000001237f46acddf58578a37e213d2a6edc4884a2fcad05ba3'
    gh = GetHeadersMessage(start_block=bytes.fromhex(block_hex))
    serialized = gh.serialize()

    answer_hex = '7f11010001a35bd0ca2f4a88c4eda6d213e2378a5758dfcd6af437120000000000000000000000000000000000000000000000000000000000000000000000000000000000'
    print("GetHeaderMessage serialized : {}".format(serialized.hex() == answer_hex))


GENESIS_BLOCK = bytes.fromhex('0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a29ab5f49ffff001d1dac2b7c')
TESTNET_GENESIS_BLOCK = bytes.fromhex('0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4adae5494dffff001d1aa4ae18')
LOWEST_BITS = bytes.fromhex('ffff001d')

def example3():
    node = SimpleNode('mainnet.programmingbitcoin.com', testnet=False, logging=True)
    node.handshake()

    genesis = Block.parse(BytesIO(GENESIS_BLOCK))
    getheaders = GetHeadersMessage(start_block=genesis.hash())
    node.send(getheaders)


class HeadersMessage:
    """
    요청한 블록헤더를 보내는/받는 커맨드
    - 연결된 상대 노드로부터 블록 헤더를 받는 과정
    - 요청을 받은 상대는 headers 커맨드를 가진 메시지를 전송
        => 해당 메시지의 페이로드가 블록 헤더 리스트
    - 헤더 메시지 구성요소
        - 블록 헤더 수
            - 1~2000 범위의 가변 정수 형식
            - 각 블록 헤더 크기는 80 바이트
        - 페이로드에 있는 트랜잭션 수
        - 트랜잭션 갯수
            - 항상 0
            - 해당 정보를 보내는 이유
                : headers 메시지와 block 메시지의 포맷을 호환하기 위해서
            - 트랜잭션 수가 0이면, 블록 전체(헤더+트랙잭션)를 파싱할 때 동일한 파싱함수 적용 가능능    """
    command = b'headers'

    def __init__(self, blocks):
        self.blocks = blocks

    @classmethod
    def parse(cls, stream):
        # 블록 헤더 수 : 가변 정수 형식
        num_headers = read_varint(stream)

        # 블록 헤더
        blocks = []
        for _ in range(num_headers):
            blocks.append(Block.parse(stream))
            num_transactions = read_varint(stream)

            # 가정 : 트랜잭션 수는 항상 0
            if num_transactions != 0:
                raise RuntimeError("Number of transaction should be 0 but {}".format(num_transactions))

        return cls(blocks)



def example4():
    from ecc.block import calculate_new_bits

    expected_bits = LOWEST_BITS
    count = 1

    previous = Block.parse(BytesIO(GENESIS_BLOCK))
    first_epoch_timestamp = previous.timestamp

    host = "199.182.184.204"
    node = SimpleNode(host, testnet=False,logging=True)
    node.handshake()
    for _ in range(19):
        getheaders = GetHeadersMessage(start_block=previous.hash())
        node.send(getheaders)
        headers = node.wait_for(HeadersMessage)
        for header in headers.blocks:
            if not header.check_pow():
                raise RuntimeError('bad PoW at block {}'.format(count))
            if header.prev_block != previous.hash():
                raise RuntimeError('discontinuous block at {}'.format(count))
            if count % 2016 == 0:
                time_diff = previous.timestamp - first_epoch_timestamp
                expected_bits = calculate_new_bits(previous.bits, time_diff)
                print(expected_bits.hex())
                first_epoch_timestamp = header.timestamp
            if header.bits != expected_bits:
                #raise RuntimeError('bad bits at block {}'.format(count))
                #print('bad bits at block {}'.format(count))
                pass
            previous = header
            count += 1



if __name__ == "__main__":
    print("Chapter 10. Networking")
    #exercise1()
    #exercise2()
    #exercise3()
    #exercise4()
    #example1()
    #example2()
    #exercise5()
    #exercise6()
    #example3()
    example4()
import hashlib

def computeMD5(str):
    hasher = hashlib.md5()
    hasher.update(str.encode("utf-8"))
    return hasher.hexdigest()


def computeSHA1(str):
    hasher = hashlib.sha1()
    hasher.update(str.encode("utf-8"))
    return hasher.hexdigest()

def computeSHA256(str):
    hasher = hashlib.sha256()
    hasher.update(str.encode("utf-8"))
    return hasher.hexdigest()

def computeSHA512(str):
    hasher = hashlib.sha512()
    hasher.update(str.encode("utf-8"))
    return hasher.hexdigest()
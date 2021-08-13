import datetime

default_zone = datetime.datetime.now()
utc_zone = datetime.datetime.now(tz=datetime.timezone.utc)

print("System Defualt Time Zone : {}".format(default_zone))
print("UTC Time Zone : {}".format(utc_zone))
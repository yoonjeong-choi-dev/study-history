import time

start = time.monotonic()

duration = 3

while True:
    next = time.monotonic()

    if next >= start + duration:
        break

    time.sleep(0.1)

print("Start time : {}".format(start))
print("End time : {}".format(next))
print("Duration : {}".format(next-start))
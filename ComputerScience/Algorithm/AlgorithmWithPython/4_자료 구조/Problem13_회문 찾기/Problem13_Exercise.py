def Palindrome_repeat(word):
    head = 0
    tail = len(word) - 1

    while head < tail:
        if word[head].isalpha() == False:
            head +=1
            continue

        elif word[tail].isalpha() == False:
            tail -=1
            continue

        elif word[head].lower() != word[tail].lower():
            return False

        else:
            head += 1
            tail -= 1


    return True


test1 = 'WoW'
test2 = "Madam, I'm Adam"
test3 = "madam, I am Adam"

print(Palindrome_repeat(test1))
print(Palindrome_repeat(test2))
print(Palindrome_repeat(test3))
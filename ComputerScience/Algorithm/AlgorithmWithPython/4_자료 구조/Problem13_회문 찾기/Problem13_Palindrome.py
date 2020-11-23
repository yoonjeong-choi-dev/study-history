def Palindrome(word):
    """
    :param word: a string
    :return: true if string is a palindrome, false if not
    """
    queue = []
    stack = []

    # put data(word) into the queue and stack
    for letter in word:
        # letter 가 공백/숫자 숫자가 아닌 알파벳인 경우만
        # 모든 알파벳은 소문자로 처리
        if letter.isalpha():
            queue.append(letter.lower())
            stack.append(letter.lower())


    # 큐와 스택에서 pop 을 이용하여 비교
    while queue:
        if queue.pop(0) != stack.pop():
            return False


    return True


test1 = 'WoW'
test2 = "Madam, I'm Adam"
test3 = "madam, I am Adam"

print(Palindrome(test1))
print(Palindrome(test2))
print(Palindrome(test3))

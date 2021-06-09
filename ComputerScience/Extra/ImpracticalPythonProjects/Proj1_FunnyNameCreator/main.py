"""
우스꽝스러운 이름 생성기
- Goal : 수립된 스타일 가이드라인(PEP8)에 맞춰 파이썬 코드로 무작위 별명 생성
- 이름과 성을 무작위로 조합하여 별명을 생성하는 프로그램
"""

import random


def main():
    """ 프로젝트 메인 함수 """
    # 프로그램 도입부
    print("Welcome to the \"Funny Name Creator \"\n")

    # 이름 데이터 로드
    first = ('Baby Oil', 'Bad News', 'Big Burps', "Bill 'Beenie-Weenie'",
             "Bob 'Stinkbug'", 'Bowel Noises', 'Boxelder', "Bud 'Lite' ",
             'Butterbean', 'Buttermilk', 'Buttocks', 'Chad', 'Chesterfield',
             'Chewy', 'Chigger', 'Cinnabuns', 'Cleet', 'Cornbread',
             'Crab Meat', 'Crapps', 'Dark Skies', 'Dennis Clawhammer',
             'Dicman', 'Elphonso', 'Fancypants', 'Figgs', 'Foncy', 'Gootsy',
             'Greasy Jim', 'Huckleberry', 'Huggy', 'Ignatious', 'Jimbo',
             "Joe 'Pottin Soil'", 'Johnny', 'Lemongrass', 'Lil Debil',
             'Longbranch', '"Lunch Money"', 'Mergatroid', '"Mr Peabody"',
             'Oil-Can', 'Oinks', 'Old Scratch', 'Ovaltine', 'Pennywhistle',
             'Pitchfork Ben', 'Potato Bug', 'Pushmeet', 'Rock Candy',
             'Schlomo', 'Scratchensniff', 'Scut', "Sid 'The Squirts'",
             'Skidmark', 'Slaps', 'Snakes', 'Snoobs', 'Snorki', 'Soupcan Sam',
             'Spitzitout', 'Squids', 'Stinky', 'Storyboard', 'Sweet Tea',
             'TeeTee', 'Wheezy Joe', "Winston 'Jazz Hands'", 'Worms')

    # 성 데이터 로드
    last = ('Appleyard', 'Bigmeat', 'Bloominshine', 'Boogerbottom',
            'Breedslovetrout', 'Butterbaugh', 'Clovenhoof', 'Clutterbuck',
            'Cocktoasten', 'Endicott', 'Fewhairs', 'Gooberdapple',
            'Goodensmith', 'Goodpasture', 'Guster', 'Henderson', 'Hooperbag',
            'Hoosenater', 'Hootkins', 'Jefferson', 'Jenkins',
            'Jingley-Schmidt', 'Johnson', 'Kingfish', 'Listenbee', "M'Bembo",
            'McFadden', 'Moonshine', 'Nettles', 'Noseworthy', 'Olivetti',
            'Outerbridge', 'Overpeck', 'Overturf', 'Oxhandler', 'Pealike',
            'Pennywhistle', 'Peterson', 'Pieplow', 'Pinkerton', 'Porkins',
            'Putney', 'Quakenbush', 'Rainwater', 'Rosenthal', 'Rubbins',
            'Sackrider', 'Snuggleshine', 'Splern', 'Stevens', 'Stroganoff',
            'Sugar-Gold', 'Swackhamer', 'Tippins', 'Turnipseed', 'Vinaigrette',
            'Walkingstick', 'Wallbanger', 'Weewax', 'Weiners', 'Whipkey',
            'Wigglesworth', 'Wimplesnatch', 'Winterkorn', 'Woolysocks')

    # 만족하는 이름이 나올 때까지 반복
    while True:
        # 이름 생성
        first_name = random.choice(first)

        # 성 생성
        last_name = random.choice(last)

        # 별명 출력
        alias = first_name + " " + last_name
        print("Your alias : {}".format(alias))

        # 만족하는지 입력
        try_again = input("Try again? (Press Enter else q to quit) : ")
        if try_again.lower() == "q":
            break

        # 가독성을 위한 개행
        print("")

    input("\nPress any key to exit")


if __name__ == "__main__":
    main()

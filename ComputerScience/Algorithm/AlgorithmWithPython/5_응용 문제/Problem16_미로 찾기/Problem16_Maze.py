"""
미로를 탈출하는 최단 경로를 찾는 문제
 - Problem15 에서의 친구찾기 문제 i.e 그래프 와 유사
"""

def solve_maze(maze, start, end):
    possible_way_qu = []
    done = set()

    # possible_way_qu : 가능성 있는 탈출 루트들의 큐
    # done : 이미 지나간 노드들
    possible_way_qu.append(start)
    done.add(start)

    while possible_way_qu:
        # possible_way : 가능성 있는 탈출 루트 (문자열)
        possible_way = possible_way_qu.pop(0)
        # last_vertex : 탈출 루트의 맨 마지막 노드
        last_vertex = possible_way[-1]
        if last_vertex == end:
            return possible_way

        for x in maze[last_vertex]:
            if x not in done:
                possible_way_qu.append(possible_way+x)
                done.add(x)
    return 'cannot solve!'





maze_ex = {
    'a': ['e'],
    'b': ['c', 'f'],
    'c': ['b'],
    'd': [],
    'e': ['a', 'i'],
    'f': ['b', 'g', 'i'],
    'g': ['f', 'h'],
    'h': ['g', 'l'],
    'i': ['e', 'm'],
    'j': ['f', 'k', 'n'],
    'k': ['j', 'o'],
    'l': ['h', 'p'],
    'm': ['i', 'n'],
    'n': ['m', 'j'],
    'o': ['k'],
    'p': ['l']
}


maze_test = {
    'a': ['c'],
    'b': ['d'],
    'c': ['a', 'd'],
    'd': ['b','c']
}

print(solve_maze(maze_ex, 'a', 'p'))

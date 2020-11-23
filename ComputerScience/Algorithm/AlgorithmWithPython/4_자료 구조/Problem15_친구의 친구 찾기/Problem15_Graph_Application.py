from __future__ import print_function

def Print_all_friend(graph, start):
    # graph : dictionary  where key : person , value : a list of friends of person
    # queue : 처리할 사람
    # done : 이미 큐에 저장한 사람

    qu = []
    done = set()

    qu.append(start)
    done.add(start)

    while qu:
        p = qu.pop(0)
        print(p)
        for friend in graph[p]:
            # friend 가 done 에 없는 경우 i.e 처리되지 않은 사람인 경우에만 큐에 저장.
            if friend not in done:
                qu.append(friend)
                done.add(friend)




def Print_all_friend_with_familiarity(graph, start):
    # graph : dictionary  where key : person , value : a list of friends of person
    # queue : 처리할 사람, 친밀도
    # done : 이미 큐에 저장한 사람

    qu = []
    done = set()

    qu.append((start, 0))
    done.add(start)

    while qu:
        (p, d) = qu.pop(0)
        print(p, d, end=' ')
        for friend in graph[p]:
            # friend 가 done 에 없는 경우 i.e 처리되지 않은 사람인 경우에만 큐에 저장.
            if friend not in done:
                qu.append((friend, d+1))
                done.add(friend)


fr_info = {
    'Summer': ['John', 'Justin', 'Mike'],
    'John': ['Summer', 'Justin'],
    'Justin': ['John', 'Summer', 'Mike', 'May'],
    'Mike': ['Summer', 'Justin'],
    'May': ['Justin', 'Kim'],
    'Kim': ['May'],
    'Tom': ['Jerry'],
    'Jerry': ['Tom']
}

Print_all_friend_with_familiarity(fr_info, 'Summer')
print()
Print_all_friend_with_familiarity(fr_info, 'Jerry')
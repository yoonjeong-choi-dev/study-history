# Problem 15
def Print_all_tree(graph, start):
    # graph : dictionary  where key : person , value : a list of friends of person
    # queue : 처리할 사람
    # done : 이미 큐에 저장한 사람

    qu = []
    done = set()

    qu.append(start)
    done.add(start)

    while qu:
        p = qu.pop(0)
        print(p, end=' ')
        for node in graph[p]:
            # friend 가 done 에 없는 경우 i.e 처리되지 않은 사람인 경우에만 큐에 저장.
            if node not in done:
                qu.append(node)
                done.add(node)



g1 = {1: [2, 3], 2:[1, 4, 5], 3: [1], 4:[2], 5: [2]}


Print_all_tree(g1, 1)
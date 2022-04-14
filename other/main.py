def cosine_similarity(a,b):
    return 0


def fitness(a,b):
    ans = cosine_similarity(a,b)
    ans = ans-1

    if ans == 0:
        return 99999
    else:
        return abs(1/ans)


solutions = []
population = []


for i in range(10000):
    ranked_population
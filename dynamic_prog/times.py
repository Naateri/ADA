####NO SE PORQUE NO FUNCIONA

class time():
    def __init__(self, start, end, cost):
        self.start = start
        self.end = end
        self.cost = cost

    def __lt__(self, t2):
        """if self.cost == t2.cost:
            if self.start == t2.start:
                return self.end < t2.end
            else:
                return self.start < t2.start
        else:
            return self.cost < t2.cost """
        if self.start == t2.start:
            if self.cost == t2.cost:
                return self.end < t2.end
            else:
                return self.cost < t2.cost
        else:
            return self.start < t2.start

    def print_s(self):
        print("start time: " + str(self.start) + ", end time: " + str(self.end) + ", cost: " + str(self.cost))


times = [[1,3,2],[2,3,4],[3,6,2],[5,7,3],[3,8,5],[7,9,3],[6,10,4]]


def max_time_bc(value,time_array,time_combo,cost = 0):
    #time_combo = [value]
    time_array_temp = time_array.copy()
    if len(time_array_temp) <= 0:
        return [True,cost]
    i = 0
    max_cost = cost
    while i < len(time_array_temp):
        #print("temp_array_temp len: " + str(len(time_array_temp)))
        if time_combo[len(time_combo)-1].end <= time_array_temp[i].start:
            rip = time_array_temp.pop(0)
            time_combo.append(rip)
            cost += rip.cost
            max_cost = cost
            result = max_time_bc(value,time_array_temp,time_combo,cost)
            if result[0]:
                return result
            time_combo.pop()
            cost -= rip.cost
        i += 1

    return [False,max_cost]
        
def find_max_time():
    time_array = list()
    for t in times:
        temp_time = time(t[0], t[1], t[2])
        time_array.append(temp_time)
    time_array.sort()
    time_combo = [time_array[0]]

    cost = max_time_bc(time_array[0],time_array,time_combo,time_array[0].cost)[1]
    while len(time_array) > 1:
        time_array.pop(0)
        time_combo = [time_array[0]]
        temp_cost = max_time_bc(time_array[0],time_array,time_combo,time_array[0].cost)[1]
        print("temp_cost: " + str(temp_cost))
        if (temp_cost > cost):
            cost = temp_cost

    return cost

print (str(find_max_time()))

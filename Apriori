# !/usr/bin/env python
# -*- coding:utf8 -*-


def load_data_set():

    # 从数据库文件中读取数据，每一行作为列表里的一条记录
    # :return: a data set


    i = 0
    data_set = []
    f = open('/root/retail.dat', 'r')
    data = f.readlines()
    for line in data:
        data_set.append(line.strip("\n").split())

    # data_set = [
    #     [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29],
    #     [30, 31, 32], [33, 34, 35],
    #     [36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46], [38, 39, 47, 48],
    #     [38, 39, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58],
    #     [32, 41, 59, 60, 61, 62], [3, 39, 48], [63, 64, 65, 66, 67, 68]]
    # print data_set
    return data_set



def create_C1(data_set):
    C1 = set()
    for t in data_set:
        for item in t:
            item_set = frozenset([item])
            C1.add(item_set)
    return C1



def is_apriori(Ck_item, Lksub1):
    for item in Ck_item:
        sub_Ck = Ck_item - frozenset([item])
        if sub_Ck not in Lksub1:
            return False
    return True


def create_Ck(Lksub1, k):
    Ck = set()
    len_Lksub1 = len(Lksub1)
    list_Lksub1 = list(Lksub1)
    for i in range(len_Lksub1):
        for j in range(1, len_Lksub1):
            l1 = list(list_Lksub1[i])
            l2 = list(list_Lksub1[j])
            l1.sort()
            l2.sort()
            if l1[0:k - 2] == l2[0:k - 2]:
                Ck_item = list_Lksub1[i] | list_Lksub1[j]
                # pruning
                if is_apriori(Ck_item, Lksub1):
                    Ck.add(Ck_item)
    return Ck



def generate_Lk_by_Ck(data_set, Ck, min_support, support_data):
    Lk = set()
    item_count = {}
    for t in data_set:
        for item in Ck:
            if item.issubset(t):
                if item not in item_count:
                    item_count[item] = 1
                else:
                    item_count[item] += 1
    t_num = float(len(data_set))
    for item in item_count:
        if (item_count[item] / t_num) >= min_support:
            Lk.add(item)
            support_data[item] = item_count[item] / t_num
    return Lk


def generate_L(data_set, k, min_support):
    support_data = {}
    C1 = create_C1(data_set)
    L1 = generate_Lk_by_Ck(data_set, C1, min_support, support_data)
    Lksub1 = L1.copy()
    L = []
    L.append(Lksub1)
    for i in range(2, k + 1):
        Ci = create_Ck(Lksub1, i)
        Li = generate_Lk_by_Ck(data_set, Ci, min_support, support_data)
        Lksub1 = Li.copy()
        L.append(Lksub1)
    return L, support_data



if __name__ == "__main__":
    load_data_set()
    data_set = load_data_set()
    L, support_data = generate_L(data_set, k=6, min_support=0.025)
    i = 0
    for Lk in L:
        print "="*50
        if len(Lk) == 0:
            break
        print "frequent " + str(len(list(Lk)[0])) + "-itemsets\t\tsupport"
        print "="*50
        for freq_set in Lk:
            print freq_set, support_data[freq_set]
